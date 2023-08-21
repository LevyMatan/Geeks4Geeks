'''
logger.py is a tool that displays logs in a table format.
It reads logs from a file and displays them in a table.
It also allows the user to filter the logs by column and value.
'''

import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QTableWidget, QTableWidgetItem, QScrollArea
from PyQt5.QtWidgets import QHeaderView, QCheckBox, QVBoxLayout, QHBoxLayout, QWidget, QLabel, QLineEdit
from PyQt5.QtGui import QColor
from PyQt5.QtCore import Qt, QTimer


class LogConfig:
    '''
    LogConfig is a class that reads a config file and stores the log configuration.
    '''

    def __init__(self, config_file_path):
        self.ignored_columns_filters = ["Time Stamp", "Line", "Message"]
        self.columns = []
        self.seperator_char = ','
        with open(config_file_path, 'r', encoding='utf-8') as config_file_handle:
            for line in config_file_handle.readlines():
                line = line.strip()
                if line.startswith('seperator'):
                    self.seperator_char = line.split('=')[1].strip()
                elif line.startswith('columns'):
                    self.columns = [column.strip() for column in line.split('=')[
                        1].split(self.seperator_char)]

    def __getitem__(self, index):
        return self.columns[index]

    def __len__(self):
        return len(self.columns)

    def __str__(self) -> str:
        return_str = 'Log Config:\n'
        return_str += f'seperator = {self.seperator_char}\n'
        return_str += 'columns=\n'
        for ind, column in enumerate(self.columns):
            return_str += f'\t{ind}) {column}\n'
        return return_str


class Logger(QMainWindow):
    '''
    Logger is a class that displays logs in a table format.
    '''

    def __init__(self, log_file, log_config_path):
        super().__init__()
        self.log_file = log_file

        # Initialize UI
        self.setWindowTitle('Logger')
        self.table = QTableWidget()
        self.setCentralWidget(self.table)
        self.sidebar = QWidget()
        self.sidebar_layout = QVBoxLayout()
        self.sidebar_label = QLabel('Filters')
        self.scroll_area = QScrollArea()
        self.search_box = QLineEdit()
        self.search_query = ''

        # Initialize Variables
        self.log_config = LogConfig(log_config_path)
        print(self.log_config)
        self.filters = {}
        self.seperator_char = self.log_config.seperator_char
        self.num_of_logs = 0
        self.log_file_pos = 0
        self.logs = []

        # Load logs from file
        self.update_logs()

        # Set up table display
        self.table.setColumnCount(len(self.log_config))
        self.table.setHorizontalHeaderLabels(self.log_config.columns)
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Interactive)
        self.table.verticalHeader().setVisible(False)
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)
        self.table.setSelectionBehavior(QTableWidget.SelectRows)
        self.table.setSelectionMode(QTableWidget.SingleSelection)

        # They are two hierarchies of filters:
        # 1. Filter by which column to filter
        # 2. Filter by which value to filter

        # Initialize filters
        self.initialize_filters()

        # Start timer to update logs
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_logs)
        self.timer.start(1000)

    def initialize_sidebar(self):
        '''
        Initialize sidebar.
        '''

        # Add search box
        self.search_box.setPlaceholderText('Search...')
        self.search_box.returnPressed.connect(self.search_logs)
        self.sidebar_layout.addWidget(self.search_box)

        # Create sidebar
        self.sidebar.setLayout(self.sidebar_layout)
        # self.sidebar.setFixedWidth(200)
        self.sidebar.setContentsMargins(0, 0, 0, 0)
        self.sidebar.setStyleSheet(
            'background-color: #76B900; border-right: 1px solid #d0d0d0;')
        # self.sidebar_label.setAlignment(Qt.AlignCenter)
        self.sidebar_label.setStyleSheet('font-weight: bold;')
        self.sidebar_layout.addWidget(self.sidebar_label)

    def initialize_filters(self):
        '''
        Initialize filters.
        '''

        # Create sidebar
        self.initialize_sidebar()

        # Choose by which column to create a filter
        self.columns_filters = {}
        for j, column in enumerate(self.log_config.columns):
            checkbox = QCheckBox(column)
            checkbox.setChecked(True)
            if column in self.log_config.ignored_columns_filters:
                checkbox.setChecked(False)
            checkbox.stateChanged.connect(self.filter_logs)
            self.columns_filters[column] = checkbox
            self.sidebar_layout.addWidget(checkbox)

        # Add filter checkboxes
        for j, column in enumerate(self.log_config.columns):
            if self.columns_filters[column].isChecked():
                values = set([log[j] for log in self.logs])
                self.filters[column] = {}
                for value in values:
                    checkbox.setStyleSheet('background-color: #76B900;')
                    checkbox = QCheckBox(value)
                    checkbox.setChecked(True)
                    checkbox.stateChanged.connect(self.filter_logs)
                    self.filters[column][value] = checkbox

        for column, filter_dict in self.filters.items():
            if not self.columns_filters[column].isChecked():
                continue
            column_label = QLabel(column)
            column_label.setStyleSheet('font-weight: bold;')
            self.sidebar_layout.addWidget(column_label)
            for value, checkbox in filter_dict.items():
                self.sidebar_layout.addWidget(checkbox)

        # Add sidebar to main window

        self.scroll_area.setWidgetResizable(True)
        self.scroll_area.setWidget(self.sidebar)
        self.scroll_area.horizontalScrollBar().setStyleSheet("QScrollBar {height:0px;}")
        self.scroll_area.verticalScrollBar().setStyleSheet("QScrollBar {width:0px;}")
        self.scroll_area.setStyleSheet('background-color: #1e1e1e; border-right: 1px solid #d0d0d0;')
        self.scroll_area.verticalScrollBar().setStyleSheet('background-color: #d0d0d0;')
        self.scroll_area.horizontalScrollBar().setStyleSheet('background-color: #d0d0d0;')
        self.main_widget = QWidget()
        self.main_layout = QHBoxLayout()
        self.main_layout.addWidget(self.table)
        self.main_layout.addWidget(self.scroll_area)
        self.main_widget.setLayout(self.main_layout)
        self.setCentralWidget(self.main_widget)

    def update_logs(self):
        '''
        Update logs from file and display them on the table.
        '''
        # Load new logs from file
        # read only from last file end position
        with open(self.log_file, 'r', encoding='utf-8') as log_file_handle:
            # Move to last file end position
            log_file_handle.seek(self.log_file_pos, 0)
            # Read new logs
            new_logs = log_file_handle.readlines()
            # Save end of file position
            self.log_file_pos = log_file_handle.tell()
        new_logs = [log.strip().split(self.seperator_char) for log in new_logs]
        self.logs += new_logs

        # Display number of logs on window title
        self.num_of_logs += len(new_logs)
        self.setWindowTitle(f'Logger ({self.num_of_logs} logs)')

        # Update table display
        self.table.setRowCount(len(self.logs))
        for i, log in enumerate(self.logs):
            if len(log) != len(self.log_config):
                continue
            for j, column in enumerate(self.log_config.columns):
                if column == 'File Origin':
                    # Only display file name
                    log[j] = log[j].split('/')[-1]
                item = QTableWidgetItem(log[j])
                self.table.setItem(i, j, item)
                # Apply highlight to search query
                self.apply_highlight(item)
            if self.filters:
                self.apply_filters(i, log)
        # Scroll to bottom if user is not looking at a specific part of the logger
        if self.table.verticalScrollBar().value() == self.table.verticalScrollBar().maximum():
            self.table.scrollToBottom()

    def apply_filters(self, i, log):
        '''
        Apply filters to log.
        '''
        visible = True
        for j, column in enumerate(self.log_config):
            if not self.columns_filters[column].isChecked():
                continue
            checkbox = self.filters[column][log[j]]
            if not checkbox.isChecked():
                visible = False
        self.table.setRowHidden(i, not visible)

    def filter_logs(self):
        '''
        Filter logs based on checkbox selection.
        '''
        # Filter logs based on checkbox selection
        for i, log in enumerate(self.logs):
            self.apply_filters(i, log)

    def apply_highlight(self, item):
        '''
        Apply highlight to search query.
        '''
        if self.search_query and item and self.search_query.lower() in item.text().lower():
            item.setBackground(QColor('#f1e740'))
        else:
            item.setBackground(QColor('#3e3e42'))

    def search_logs(self):
        '''
        Search logs based on search query.
        '''
        # Search logs based on search query
        self.search_query = self.search_box.text()
        for i in range(self.table.rowCount()):
            for j in range(self.table.columnCount()):
                item = self.table.item(i, j)
                self.apply_highlight(item)

if __name__ == '__main__':
    app = QApplication([])
    logger = Logger('log.txt', "config_file.txt")
    logger.show()
    sys.exit(app.exec_())
