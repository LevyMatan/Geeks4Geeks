'''
Port Mapping

The script takes as an input a path to a prs file and 
is used to generate the following files:
    - module_db.csv
    - ugl_configurations_ga_owner_*.csv
    - cport_configurations_ga_owner_*.csv

There are a few global variables that can be changed:
    - PORT_WIDTH: number of lanes per port
    - MODULE_WIDTH: number of lanes per module
    - ENABLE_DEBUG_PRINTS: enable/disable debug prints

Important: Use a full PRS file, there is an assumptions the relevant module database section 
comes after the line '[non_isfu_config]'.
If there is a change in the PRS structure this script need to be updated.

module_db.csv columns:
    - module_idx
    - module_lane
    - tx_serdes
    - tx_polarity
    - rx_serdes
    - rx_polarity
    - ib_port
    - ga_lane_owner
    - local_port
    - local_lane
    - cport
    - cport_lane

ugl_configurations_ga_owner_*.csv columns:
    - ugl_idx
    - ugl_lane
    - tx_log2phy_sel
    - rx_log2phy_sel
    - ugl_lane//4
    - rx_logic_reversal_16to8

cport_configurations_ga_owner_*.csv columns:
    - cport_idx
    - cport_lane
    - ugl2plu_tx_sel_lane
    - ugl2plu_rx_sel_lane
    - ioplc_rx_16x_reversal_sel

Useage example:
    python port_mapping.py prs.prs
'''
import argparse
import re

# Adjust these values based on the device
PORT_WIDTH = 2
MODULE_WIDTH = 8

class DeviceParams:
    '''
    Device parameters
    '''
    def __init__(self, device_name="Sunbird"):
        if device_name.lower() == "sunbird":
            self.CPORT_WIDTH = 4
            self.UGL_WIDTH = 12
            self.NUM_OF_UGLS = 13
            self.NUM_OF_LANES_IN_CHIP = 144
            self.NUM_OF_LANES_IN_8X = 8
            self.NUM_OF_LOCAL_PORTS_IN_8X = 8
        if device_name.lower() == "blackbird":
            self.CPORT_WIDTH = 8
            self.UGL_WIDTH = 12
            self.NUM_OF_UGLS = 12
            self.NUM_OF_LANES_IN_CHIP = 576 #
            self.NUM_OF_LANES_IN_8X = 8
            self.NUM_OF_LOCAL_PORTS_IN_8X = 4

DEVICE = DeviceParams("sunbird")
# Debug prints
ENABLE_DEBUG_PRINTS = True

# Specific Functions Prints
ENABLE_DEBUG_PARSE_MODULE_DATABASE = False
ENABLE_DEBUG_GET_PORT_MAPPING = False
ENABLE_DEBUG_EXPORT_MODULE_DB_TO_CSV = False
ENABLE_DEBUG_EXPORT_MODULE_DB_TO_CSV = False


def debug_print(msg):
    '''
    Debug print
    '''
    if ENABLE_DEBUG_PRINTS:
        print(msg)


class Module:
    '''
    Module
    '''

    def __init__(self):
        self.num_of_lanes = MODULE_WIDTH
        self.module_idx = 0
        self.tx_serdes_lanes = [0] * self.num_of_lanes
        self.rx_serdes_lanes = [0] * self.num_of_lanes
        self.local_port = [0] * self.num_of_lanes
        self.local_lane = [0] * self.num_of_lanes
        self.cport = [0] * self.num_of_lanes
        self.cport_lane = [0] * self.num_of_lanes
        self.ib_port = [0] * self.num_of_lanes
        self.rx_polarity = [0] * self.num_of_lanes
        self.tx_polarity = [0] * self.num_of_lanes
        self.ga_lane_owner = [0] * self.num_of_lanes

    def resize_module(self, new_length):
        '''
        Resize module
        '''
        self.num_of_lanes = new_length
        self.tx_serdes_lanes = self.tx_serdes_lanes[:new_length]
        self.rx_serdes_lanes = self.rx_serdes_lanes[:new_length]
        self.local_port = self.local_port[:new_length]
        self.local_lane = self.local_lane[:new_length]
        self.cport = self.cport[:new_length]
        self.ib_port = self.ib_port[:new_length]
        self.rx_polarity = self.rx_polarity[:new_length]
        self.tx_polarity = self.tx_polarity[:new_length]
        self.ga_lane_owner = self.ga_lane_owner[:new_length]


def parse_module_database(filename):
    '''
    Parse module database
    '''
    ga_lane_owners = []
    modules = []
    with open(filename, 'r', encoding='utf-8') as file:
        module_db_started = False
        module_num = -1
        for line in file:
            if line.startswith('[non_isfu_config]'):
                module_db_started = True

            if module_db_started:
                if line.startswith(';;;;; module'):

                    debug_print(f"module_num: {module_num}, line: {line}")
                    if (module_num >= 0 and last_lane < modules[module_num].num_of_lanes):
                        # Resize module
                        modules[module_num].resize_module(last_lane)
                    # New module
                    module_num += 1
                    modules.append(Module())
                else:

                    # Parse lane data
                    match = re.match(
                        r'module\.num\[(\d+)\]\.m2l\.(\w+)\.lane\[(\d+)\]\.(\w+)\s*=\s*(\d+)', line)
                    debug_print(f"line: {line}, match: {match}")
                    if match:
                        module_idx = int(match.group(1))
                        lane_type = match.group(2)
                        lane_num = int(match.group(3))
                        lane_attribute = match.group(4)
                        value = int(match.group(5))

                        # Debug: print parsed data
                        debug_print(
                            f'module_idx: {module_idx}, lane_type: {lane_type}, lane_num: {lane_num}, lane_attribute: {lane_attribute}, value: {value}')
                        last_lane = lane_num + 1

                        if 'serdes' == lane_attribute:
                            if lane_type == 'tx':
                                modules[module_num].tx_serdes_lanes[lane_num] = value
                                if 0 == lane_num:
                                    modules[module_num].module_idx = module_idx
                            elif lane_type == 'rx':
                                modules[module_num].rx_serdes_lanes[lane_num] = value
                        elif 'polarity' == lane_attribute:
                            if lane_type == 'tx':
                                modules[module_num].tx_polarity[lane_num] = value
                            elif lane_type == 'rx':
                                modules[module_num].rx_polarity[lane_num] = value
                        elif 'ga_lane_owner' == lane_attribute:
                            ga_lane_owners.append(value)
                            modules[module_num].ga_lane_owner[lane_num] = value
                        elif 'ib_port' == lane_attribute:
                            modules[module_num].ib_port[lane_num] = value

    # Resize module
    if ((module_num >= 0) and (last_lane < modules[module_num].num_of_lanes)):
        modules[module_num].resize_module(last_lane)

    # Debug: print all modules
    for module in modules:
        debug_print(f'module_idx: {module.module_idx}')
        debug_print(f'    tx_serdes_lanes: {module.tx_serdes_lanes}')
        debug_print(f'    rx_serdes_lanes: {module.rx_serdes_lanes}')
        debug_print(f'    tx_polarity: {module.tx_polarity}')
        debug_print(f'    rx_polarity: {module.rx_polarity}')
        debug_print(f'    ga_lane_owner: {module.ga_lane_owner}')
        debug_print(f'    ib_port: {module.ib_port}')

    # Remove duplicates from ga lane owners
    ga_lane_owners = list(set(ga_lane_owners))
    if not ga_lane_owners:
        ga_lane_owners.append(0)

    # Debug: print all ga lane owners
    debug_print(f'ga_lane_owners: {ga_lane_owners}')

    return modules, ga_lane_owners


def get_port_mapping(modules_list, ga_owner):
    '''
    Get port mapping
    '''
    group_8x_counter = [0] * ((DEVICE.NUM_OF_LANES_IN_CHIP // DEVICE.NUM_OF_LANES_IN_8X) + 1)
    cport_lane_counter = [-1] * (DEVICE.NUM_OF_LANES_IN_CHIP // DEVICE.CPORT_WIDTH + 1)
    for module in modules_list:
        for lane in range(module.num_of_lanes):
            if ga_owner == module.ga_lane_owner[lane]:
                group_8x_id = module.tx_serdes_lanes[lane] // DEVICE.NUM_OF_LANES_IN_8X
                local_port_base = group_8x_id * DEVICE.NUM_OF_LOCAL_PORTS_IN_8X
                local_port_offset = group_8x_counter[group_8x_id]
                local_port = 1 + local_port_base + local_port_offset
                local_lane = lane % PORT_WIDTH
                group_8x_counter[group_8x_id] = group_8x_counter[group_8x_id] + \
                    ((1 + local_lane) // PORT_WIDTH) * PORT_WIDTH
                cport = (local_port - 1) // DEVICE.CPORT_WIDTH
                cport_lane_counter[cport] = cport_lane_counter[cport] + 1
                module.local_port[lane] = local_port
                module.local_lane[lane] = local_lane
                module.cport[lane] = cport
                module.cport_lane[lane] = cport_lane_counter[cport]
                debug_print(f'module: {module.module_idx}, module_lane: {lane}, group_8x_id: {group_8x_id}, local_port_base: {local_port_base}, local_port_offset: {local_port_offset}, local_port: {local_port}, local_lane: {local_lane}, cport: {cport}')


def export_module_db_to_csv(module_list):
    '''
    Export module db to csv
    The top level header is: Index, Input, Local Port Mapping, Cport Mapping, Ugl Mapping
    Under Index:
        - module_idx
        - module_lane
    Under Input:
        - tx_serdes
        - tx_polarity
        - rx_serdes
        - rx_polarity
        - ib_port
        - ga_lane_owner
    Under Local Port Mapping:
        - local_port
        - local_lane
    Under Cport Mapping:
        - cport
        - cport_lane
    Under Ugl Mapping
        - TX UGL idx
        - TX UGL lane
        - RX UGL idx
        - RX UGL lane
        
    '''
    with open(f'{DEVICE_HEADER}_module_db.csv', 'w', encoding='utf-8') as csv_file:
        csv_file.write('Index,,Input,,,,,,Local Port Mapping,,Cport Mapping,,UGL Mapping\n')
        csv_file.write(
            'module_idx,module_lane,tx_serdes,tx_polarity,rx_serdes,rx_polarity,ib_port,ga_lane_owner,local_port,local_lane,cport,cport_lane,tx_ugl_idx,tx_ugl_lane,rx_ugl_idx,rx_ugl_lane\n')
        for module in module_list:
            for lane in range(module.num_of_lanes):
                tx_serdes_lane = module.tx_serdes_lanes[lane]
                tx_polarity = module.tx_polarity[lane]
                rx_serdes_lane = module.rx_serdes_lanes[lane]
                rx_polarity = module.rx_polarity[lane]
                ib_port = module.ib_port[lane]
                ga_lane_owner = module.ga_lane_owner[lane]
                local_port = module.local_port[lane]
                local_lane = module.local_lane[lane]
                cport = module.cport[lane]
                cport_lane = module.cport_lane[lane]
                tx_ugl_idx = tx_serdes_lane // DEVICE.UGL_WIDTH
                tx_ugl_lane = tx_serdes_lane % DEVICE.UGL_WIDTH
                rx_ugl_idx = rx_serdes_lane // DEVICE.UGL_WIDTH
                rx_ugl_lane = rx_serdes_lane % DEVICE.UGL_WIDTH
                csv_file.write(
                    f'{module.module_idx},{lane},{tx_serdes_lane},{tx_polarity},{rx_serdes_lane},{rx_polarity},{ib_port},{ga_lane_owner},{local_port},{local_lane},{cport},{cport_lane},{tx_ugl_idx},{tx_ugl_lane},{rx_ugl_idx},{rx_ugl_lane}\n')


class Ugl:
    '''
    UGL
    '''

    def __init__(self):
        self.num_of_lanes = DEVICE.UGL_WIDTH
        self.tx_log2phy_sel = [0] * self.num_of_lanes
        self.rx_log2phy_sel = [0] * self.num_of_lanes
        self.rx_logic_reversal_16to8 = [0] * (self.num_of_lanes // DEVICE.CPORT_WIDTH)


def compute_ugl_reversals(module_list, ga_owner):
    '''
    Compute the configuration of the UGL reversals
    There are 3 configurations:
    1) TX - 8X reversals
        # UglTx = physical_lane_tx//12
        # UglTxLane = physical_lane_tx%12
        # logical_lane = cport * CPORT_WIDTH + cport_lane
        # top.iopl_ugl[$UglTx].uglpl.sunbird_iopl_reversals.tx_log2phy_sel[$UglTxLane].tx_log2phy_sel = $logical_lane%8
    2) RX - 8X reversals
        # UglRx = physical_lane_rx//12
        # UglRxLane = physical_lane_rx%12
        # logical_lane = cport * CPORT_WIDTH + cport_lane
        # top.iopl_ugl[$UglRx].uglpl.sunbird_iopl_reversals.rx_log2phy_sel[$UglRxLane].rx_log2phy_sel = $logical_lane%8
    3) RX - 16X reversals
        # Ugl16XReversal = (logical_lane/8 != physical_lane_rx/8) ^ (((physical_lane_rx/8)%9)%2)
        # top.iopl_ugl[$UglRx].uglpl.sunbird_iopl_reversals.rx_logic_reversal_16to8[($physical_lane_rx%12)/4] = $Ugl16XReversal
    '''
    ugl_hw_configurations = [Ugl() for _ in range(DEVICE.NUM_OF_UGLS + 1)]

    for module_idx, module in enumerate(module_list):
        for lane in range(module.num_of_lanes):
            if ga_owner == module.ga_lane_owner[lane]:
                cport = module.cport[lane]
                cport_lane = module.cport_lane[lane]
                logical_lane = cport * DEVICE.CPORT_WIDTH + cport_lane
                # 1) TX - 8X reversals
                ugl_tx = module.tx_serdes_lanes[lane] // DEVICE.UGL_WIDTH
                ugl_tx_lane = module.tx_serdes_lanes[lane] % DEVICE.UGL_WIDTH
                ugl_hw_configurations[ugl_tx].tx_log2phy_sel[ugl_tx_lane] = logical_lane % DEVICE.NUM_OF_LANES_IN_8X
                debug_print(
                    f'module_idx: {module_idx}, lane: {lane}, ugl_tx: {ugl_tx}, ugl_tx_lane: {ugl_tx_lane}, tx_log2phy_sel: {logical_lane % DEVICE.NUM_OF_LANES_IN_8X}')
                # 2) RX - 8X reversals
                ugl_rx = module.rx_serdes_lanes[lane] // DEVICE.UGL_WIDTH
                ugl_rx_lane = module.rx_serdes_lanes[lane] % DEVICE.UGL_WIDTH
                ugl_hw_configurations[ugl_rx].rx_log2phy_sel[ugl_rx_lane] = logical_lane % DEVICE.NUM_OF_LANES_IN_8X
                # 3) RX - 16X reversals
                ugl_16x_reversal = ((logical_lane // DEVICE.NUM_OF_LANES_IN_8X) != (module.rx_serdes_lanes[lane] // DEVICE.NUM_OF_LANES_IN_8X)) ^ (
                    ((module.rx_serdes_lanes[lane] // DEVICE.NUM_OF_LANES_IN_8X) % 9) % 2)
                ugl_hw_configurations[ugl_rx].rx_logic_reversal_16to8[ugl_rx_lane //
                                                                      4] = ugl_16x_reversal

    # Debug: print all ugl configurations
    for ugl_idx, ugl in enumerate(ugl_hw_configurations):
        debug_print(f'ugl_idx: {ugl_idx}')
        debug_print(f'    tx_log2phy_sel: {ugl.tx_log2phy_sel}')
        debug_print(f'    rx_log2phy_sel: {ugl.rx_log2phy_sel}')
        debug_print(
            f'    rx_logic_reversal_16to8: {ugl.rx_logic_reversal_16to8}')

    return ugl_hw_configurations


def export_ugl_configurations_to_csv(ugl_hw_configurations, ga_owner):
    '''
    Export UGL configurations to csv
    '''
    with open(f'{DEVICE_HEADER}_ugl_configurations_ga_owner_{ga_owner}.csv', 'w', encoding='utf-8') as csv_file:
        csv_file.write(
            'ugl_idx,ugl_lane,ugl_lane//4,tx_log2phy_sel,rx_log2phy_sel,rx_logic_reversal_16to8\n')
        for ugl_idx, ugl in enumerate(ugl_hw_configurations):
            for ugl_lane in range(ugl.num_of_lanes):
                csv_file.write(
                    f'{ugl_idx},{ugl_lane},{ugl_lane//4},{ugl.tx_log2phy_sel[ugl_lane]},{ugl.rx_log2phy_sel[ugl_lane]},{ugl.rx_logic_reversal_16to8[ugl_lane//4]}\n')


class Cport:
    '''
    Cport
    '''

    def __init__(self):
        self.num_of_lanes = DEVICE.CPORT_WIDTH
        self.ugl2plu_tx_sel_lane = [0] * self.num_of_lanes
        self.ugl2plu_rx_sel_lane = [0] * self.num_of_lanes
        self.ioplc_rx_16x_reversal_sel = [0] * self.num_of_lanes


def compute_cport_reversals(module_list, ga_owner):
    '''
    Compute the configuration of the Cport reversals
    There are 3 configurations:
    1) TX - 8X reversals
        # top.ports.cluster[$Cport].pmux.pmux.ugl2p_8x_reversal.ugl2plu_tx_sel_lane[$CportLane] = $physical_lane_tx%8
    2) RX - 8X reversals
        # top.ports.cluster[$Cport].pmux.pmux.ugl2p_8x_reversal.ugl2plu_rx_sel_lane[$CportLane] = $physical_lane_rx%8
    3) RX - 16X reversals
        # Cport16XReversal = (logical_lane/8 != physical_lane_rx/8) ^ (((logical_lane/8)%9)%2)
        # top.ports.cluster[$Cport].pmux.pmux.ioplc_rx_16x_reversal_sel = $Cport16XReversal
    '''
    cport_hw_configurations = [Cport() for _ in range((DEVICE.NUM_OF_LANES_IN_CHIP // DEVICE.CPORT_WIDTH) + 1)]
    for module in module_list:
        for lane in range(module.num_of_lanes):
            if ga_owner == module.ga_lane_owner[lane]:
                cport = module.cport[lane]
                cport_lane = module.cport_lane[lane]
                logical_lane = cport * DEVICE.CPORT_WIDTH + cport_lane
                # 1) TX - 8X reversals
                debug_print(
                    f'lane: {lane}, cport: {cport}, cport_lane: {cport_lane}, ugl2plu_tx_sel_lane: {module.tx_serdes_lanes[lane] % DEVICE.NUM_OF_LANES_IN_8X}')
                cport_hw_configurations[cport].ugl2plu_tx_sel_lane[cport_lane] = module.tx_serdes_lanes[lane] % DEVICE.NUM_OF_LANES_IN_8X
                # 2) RX - 8X reversals
                cport_hw_configurations[cport].ugl2plu_rx_sel_lane[cport_lane] = module.rx_serdes_lanes[lane] % DEVICE.NUM_OF_LANES_IN_8X
                # 3) RX - 16X reversals
                cport_hw_configurations[cport].ioplc_rx_16x_reversal_sel[cport_lane] = (
                    (logical_lane // DEVICE.NUM_OF_LANES_IN_8X) != (module.rx_serdes_lanes[lane] // DEVICE.NUM_OF_LANES_IN_8X)) ^ (((logical_lane // DEVICE.NUM_OF_LANES_IN_8X) % 9) % 2)

    # Debug: print all cport configurations
    for cport_idx, cport in enumerate(cport_hw_configurations):
        debug_print(f'cport_idx: {cport_idx}')
        debug_print(f'    ugl2plu_tx_sel_lane: {cport.ugl2plu_tx_sel_lane}')
        debug_print(f'    ugl2plu_rx_sel_lane: {cport.ugl2plu_rx_sel_lane}')
        debug_print(f'    ioplc_rx_16x_reversal_sel: {cport.ioplc_rx_16x_reversal_sel}')

    return cport_hw_configurations


def export_cport_configurations_to_csv(cport_hw_configurations, ga_owner):
    '''
    Export Cport configurations to csv
    '''
    with open(f'{DEVICE_HEADER}_cport_configurations_ga_owner_{ga_owner}.csv', 'w', encoding='utf-8') as csv_file:
        csv_file.write(
            'cport_idx,cport_lane,ugl2plu_tx_sel_lane,ugl2plu_rx_sel_lane,ioplc_rx_16x_reversal_sel\n')
        for cport_idx, cport in enumerate(cport_hw_configurations):
            for cport_lane in range(cport.num_of_lanes):
                csv_file.write(
                    f'{cport_idx},{cport_lane},{cport.ugl2plu_tx_sel_lane[cport_lane]},{cport.ugl2plu_rx_sel_lane[cport_lane]},{cport.ioplc_rx_16x_reversal_sel[cport_lane]}\n')


if '__main__' == __name__:

    parser = argparse.ArgumentParser(description='Port mapping')
    parser.add_argument('prs_file', help='Path to prs file\n\
Important: Use a full PRS file, there is an assumptions the relevant module database section\n\
comes after the line "[non_isfu_config]".\n\
If there is a change in the PRS structure this script need to be updated.',
                        type=str, default='prs.prs')
    args = parser.parse_args()
    debug_print(f'prs_file: {args.prs_file}')

    # Parse module database
    module_list, ga_owners = parse_module_database(args.prs_file)

    # Debug: ga owners
    debug_print(f'ga_owners: {ga_owners}')

    # Strip prs file name from the path and remove the extension
    DEVICE_HEADER = args.prs_file.split('/')[-1].split('.')[0]

    # Map ports
    for ga_owner in ga_owners:
        debug_print(f"Start Mapping of ga_owner: {ga_owner}")
        get_port_mapping(module_list, ga_owner)

    # Export module database to csv
    export_module_db_to_csv(module_list)

    # Compute UGL and Cport configurations and export to CSV
    for ga_owner in ga_owners:
        ugl_hw_configurations = compute_ugl_reversals(module_list, ga_owner)
        export_ugl_configurations_to_csv(ugl_hw_configurations, ga_owner)
        cport_hw_configurations = compute_cport_reversals(module_list, ga_owner)
        export_cport_configurations_to_csv(cport_hw_configurations, ga_owner)
