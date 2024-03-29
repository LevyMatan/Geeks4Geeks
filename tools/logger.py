'''
logger.py is a tool that displays logs in a table format.
It reads logs from a file and displays them in a table.
It also allows the user to filter the logs by column and value.
'''
import sys
import argparse
from PyQt5.QtWidgets import QApplication, QMainWindow, QTableWidget, QTableWidgetItem, QCompleter, QMessageBox
from PyQt5.QtWidgets import QHeaderView, QCheckBox, QVBoxLayout, QHBoxLayout, QWidget, QLabel, QDialog
from PyQt5.QtWidgets import QLineEdit, QScrollArea, QPushButton, QColorDialog, QSplitter, QComboBox
from PyQt5.QtGui import QColor
from PyQt5.QtCore import QTimer, Qt, QEvent, pyqtSignal

class LogConfig:
    '''
    LogConfig is a class that reads a config file and stores the log configuration.
    '''
    def __init__(self, config_file_path):
        self.ignored_columns_filters = ["Time Stamp", "Line", "Message"]
        self.columns = []
        self.seperator_char = ','
        with open(config_file_path, encoding='utf-8') as config_file_handle:
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

class SearchBox(QDialog):
    '''
    SearchBox is a class that creates a search box dialog.
    '''
    # Define the search_signal attribute as a pyqtSignal
    search_signal = pyqtSignal(str, bool)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.find_next = False

        self.setWindowTitle("Search")
        self.setModal(True)

        # Create the search label and line edit
        search_label = QLabel("Search:")
        self.search_line_edit = QLineEdit()
        self.search_line_edit.textChanged.connect(self.reset_search)
        self.search_line_edit.returnPressed.connect(self.search)

        # Create the search and cancel buttons
        self.search_button = QPushButton("Find")
        self.search_button.clicked.connect(self.search)
        cancel_button = QPushButton("Cancel")
        cancel_button.clicked.connect(self.reject)

        # Add the widgets to the layout
        layout = QHBoxLayout()
        layout.addWidget(search_label)
        layout.addWidget(self.search_line_edit)
        layout.addWidget(self.search_button)
        layout.addWidget(cancel_button)
        self.setLayout(layout)

    def reset_search(self):
        '''
        Reset search.
        '''
        self.find_next = False
        self.search_button.setText("Find")

    def search(self):
        '''
        Set the find_next attribute to True and change the button text
        '''
        self.find_next = True
        self.search_button.setText("Find Next")
        # Call the QDialog.accept method and return QDialog.Accepted
        super().accept()
        return QDialog.Accepted

    def get_find_next(self):
        '''
        Get find next.
        '''
        return self.find_next

    def get_search_text(self):
        '''
        Get search text.
        '''
        return self.search_line_edit.text()

class Highlighter:
    '''
    Highlighter is a class that create a text box for user input and a color palate to choose from.
    '''
    def __init__(self, color='#ff9300', text='Highlight...', action_function=None):
        self.color = color
        self.text = text
        self.action_function = action_function

        self.layout = QHBoxLayout()

        self.highlight_box = QLineEdit()
        self.highlight_box.setPlaceholderText(self.text)
        self.highlight_box.returnPressed.connect(self.set_highlight_text)

        self.color_picker_button = QPushButton('')
        self.color_picker_button.setFixedSize(20, 20)
        self.color_picker_button.setStyleSheet('background-color: {self.color};')
        self.color_picker_button.clicked.connect(self.set_color_picker)

        self.layout.addWidget(self.highlight_box)
        self.layout.addWidget(self.color_picker_button)

    def __str__(self) -> str:
        return f'color = {self.color}\ntext = {self.text}'

    def get_color(self):
        '''
        Get highlight color.
        '''
        return self.color

    def set_color(self, color):
        '''
        Set highlight color.
        '''
        self.color = color

    def get_text(self):
        '''
        Get highlight text.
        '''
        return self.text

    def set_text(self, text):
        '''
        Set highlight text.
        '''
        self.text = text

    def update_button_color(self):
        '''
        Update color picker button color.
        '''
        self.color_picker_button.setStyleSheet(f'background-color: {self.color};')

    def set_color_picker(self):
        '''
        Show color picker dialog.
        Update color picker button color.
        Save color.
        '''
        color = QColorDialog.getColor()
        if color.isValid():
            self.color = color.name()
            self.update_button_color()

    def set_highlight_text(self):
        '''
        Save highlight text.
        '''
        self.text = self.highlight_box.text()
        self.action_function(self.text, self.color)

    def get_layout(self):
        '''
        Get layout.
        '''
        return self.layout

class Logger(QMainWindow):
    '''
    Logger is a class that displays logs in a table format.
    '''

    def eventFilter(self, obj, event):
        '''
        Override event filter to create a search shortcut.
        '''
        if event.type() == QEvent.ShortcutOverride:
            if event.key() == Qt.Key_F and event.modifiers() == Qt.ControlModifier:
                self.show_search_box()
                return True
        return super().eventFilter(obj, event)

    def __init__(self, log_file, log_config_path):
        super().__init__()
        self.resize(1000, 600)
        self.log_file = log_file

        # Initialize UI
        self.setWindowTitle('Logger')
        self.table = QTableWidget()
        self.sidebar = QWidget()
        self.scroll_area = QScrollArea()

        # Create the search box dialog
        self.search_box = SearchBox(self)

        # Install the shortcut event filter
        self.installEventFilter(self)

        # Initialize Variables
        self.last_found_item_index = None
        self.log_config = LogConfig(log_config_path)
        print(self.log_config)
        self.filters = {}
        self.seperator_char = self.log_config.seperator_char
        self.num_of_logs = 0
        self.log_file_pos = 0
        self.logs = []
        self.double_click_color = '#76B900'
        self.double_click_text = ''
        # Load logs from file
        self.update_logs()

        # Set up table display
        self.table.setColumnCount(len(self.log_config))
        self.table.setHorizontalHeaderLabels(self.log_config.columns)
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)
        # self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Interactive)
        self.table.horizontalHeader().setStretchLastSection(True)
        self.table.verticalHeader().setVisible(False)
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)
        self.table.setSelectionBehavior(QTableWidget.SelectRows)
        self.table.setSelectionMode(QTableWidget.SingleSelection)
        self.table.cellDoubleClicked.connect(self.on_cell_double_clicked)

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
        # Create sidebar
        sidebar_layout = QVBoxLayout()
        self.sidebar.setContentsMargins(0, 0, 0, 0)
        self.sidebar.setStyleSheet(
            'background-color: #e8ffe4; border-right: 1px solid #d0d0d0;')

        # Create clear logs button
        clear_logs_button = QPushButton('Clear Logs')
        clear_logs_button.clicked.connect(self.clear_logs)
        sidebar_layout.addWidget(clear_logs_button)

        # Create highlighter
        highlighter_label = QLabel('Highlight Logs')
        highlighter_label.setStyleSheet('font-weight: bold;')
        sidebar_layout.addWidget(highlighter_label)
        self.sidebar.highlighter = Highlighter(action_function=self.highlight_logs)
        sidebar_layout.addLayout(self.sidebar.highlighter.get_layout())

        # Create sidebar label
        sidebar_label = QLabel('Filter Logs')
        sidebar_label.setStyleSheet('font-weight: bold;')
        sidebar_layout.addWidget(sidebar_label)


        # Set sidebar layout
        self.sidebar.setLayout(sidebar_layout)
        self.sidebar.highlighter.update_button_color()

    def initialize_filters(self):
        '''
        Initialize filters.
        '''
        # Create sidebar
        self.initialize_sidebar()

        # Choose by which column to create a filter
        self.columns_filters = {}
        for j, column in enumerate(self.log_config.columns):
            if column in self.log_config.ignored_columns_filters:
                continue
            checkbox = QCheckBox(column)
            checkbox.setChecked(True)
            checkbox.stateChanged.connect(lambda state, text=column : self.select_all_checkboxes(state, text))
            checkbox.setStyleSheet('font-weight: bold;')

            if column in self.log_config.ignored_columns_filters:
                checkbox.setChecked(False)
            checkbox.stateChanged.connect(self.filter_logs)
            self.columns_filters[column] = checkbox

        # Add filter checkboxes
        for j, column in enumerate(self.log_config.columns):
            if column in self.log_config.ignored_columns_filters:
                continue
            values = {log[j] for log in self.logs}
            values = sorted(values)
            self.filters[column] = {}
            for value in values:
                checkbox = QCheckBox(value)
                checkbox.setChecked(True)
                checkbox.stateChanged.connect(self.filter_logs)
                self.filters[column][value] = checkbox

        for column, filter_dict in self.filters.items():

            filter_header_layout = QHBoxLayout()
            filter_header_layout.addWidget(self.columns_filters[column])
            choose_function_dropdown = QComboBox()
            choose_function_dropdown.addItems(filter_dict.keys())
            choose_function_dropdown.setEditable(True)
            completer = QCompleter(filter_dict.keys())
            choose_function_dropdown.setCompleter(completer)
            choose_function_dropdown.activated[str].connect(lambda text, column=column : self.toggle_filter(text, column))
            filter_header_layout.addWidget(choose_function_dropdown)
            self.sidebar.layout().addLayout(filter_header_layout)

            for value, checkbox in filter_dict.items():
                self.sidebar.layout().addWidget(checkbox)

        # Add sidebar to main window
        self.scroll_area.setWidgetResizable(True)
        self.scroll_area.setStyleSheet(
            'background-color: #FFFFFF; border-right: 1px solid #d0d0d0;')
        self.scroll_area.horizontalScrollBar().setStyleSheet(
            "QScrollBar {height:0px;}")
        self.scroll_area.verticalScrollBar().setStyleSheet(
            "QScrollBar {width:0px;}")
        self.scroll_area.verticalScrollBar().setStyleSheet('background-color: #d0d0d0;')
        self.scroll_area.horizontalScrollBar().setStyleSheet('background-color: #d0d0d0;')
        self.scroll_area.setWidget(self.sidebar)

        self.main_widget = QSplitter(Qt.Horizontal)
        # self.main_layout = QHBoxLayout()
        self.main_widget.addWidget(self.table)
        self.main_widget.addWidget(self.scroll_area)
        # self.main_widget.setLayout(self.main_layout)
        self.setCentralWidget(self.main_widget)
        self.main_widget.setSizes([int(self.width() * 0.75), int(self.width() * 0.25)])

    def update_logs(self):
        '''
        Update logs from file and display them on the table.
        '''
        # Read only from last file end position
        with open(self.log_file, encoding='utf-8') as log_file_handle:
            # Move to last file end position
            log_file_handle.seek(self.log_file_pos, 0)
            # Read new logs
            new_logs = log_file_handle.readlines()
            # Save end of file position
            self.log_file_pos = log_file_handle.tell()

        # if new_logs == []:
        #     return
        new_logs = [log.strip().split(self.seperator_char) for log in new_logs if log.count(self.log_config.seperator_char) == (len(self.log_config)-1)]
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
                if column == 'Origin File':
                    # Only display file name
                    log[j] = log[j].split('/')[-1]
                item = QTableWidgetItem(log[j])
                self.table.setItem(i, j, item)
                # Apply highlight to search query
                try:
                    text_query = self.sidebar.highlighter.get_text()
                    highlight_color = self.sidebar.highlighter.get_color()
                    self.apply_highlight_to_table_cell(item, text_query, highlight_color)
                except(AttributeError):
                    # If highlighter is not initialized yet
                    pass
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
            if column in self.log_config.ignored_columns_filters:
                continue
            checkbox = self.filters[column][log[j]]
            if not checkbox.isChecked():
                visible = False
        self.table.setRowHidden(i, not visible)

    def toggle_filter(self, text, column):
        '''
        Toggle filter checkbox.
        '''
        self.filters[column][text].toggle()

    def filter_logs(self):
        '''
        Filter logs based on checkbox selection.
        '''
        # Filter logs based on checkbox selection
        for i, log in enumerate(self.logs):
            self.apply_filters(i, log)

    def apply_highlight_to_table_cell(self, item, highlight_query, highlight_color):
        '''
        Apply highlight to row if search query is found.
        '''
        def find_index_of_target_string(strings, target):
            for i, search_str in enumerate(strings):
                if search_str and search_str.lower() in target:
                    return i
            return None

        highlight_query = [self.double_click_text, highlight_query]
        highlight_color = [self.double_click_color, highlight_color]

        if item is None:
            return
        ind = find_index_of_target_string(highlight_query, item.text().lower())
        if ind is not None:
            item.setBackground(QColor(highlight_color[ind]))
        else:
            item.setBackground(QColor('#FFFFFF'))

    def highlight_logs(self, text, color):
        '''
        Highlight logs based on search query.
        '''
        # Search logs based on search query
        for i in range(self.table.rowCount()):
            for j in range(self.table.columnCount()):
                item = self.table.item(i, j)
                self.apply_highlight_to_table_cell(item, text, color)

    def on_cell_double_clicked(self, row, column):
        '''
        Highlight logs based on cell clicked.
        '''
        item = self.table.item(row, column)
        if item is None:
            return
        # Set the old value to white
        self.double_click_color = '#FFFFFF'
        self.highlight_logs(self.double_click_text, self.double_click_color)

        self.double_click_color = '#76B900'
        # Now, if the value is the same as before, set the text to empty
        if self.double_click_text == item.text():
            self.double_click_text = ''
        else:
            self.double_click_text = item.text()
            self.highlight_logs(self.double_click_text, self.double_click_color)

    def select_all_checkboxes(self, state, text):
        '''
        select all checkboxes in a column.
        '''
        set_checked = False
        if state == Qt.Checked:
            set_checked = True
        for checkbox in self.filters[text].values():
            checkbox.setChecked(set_checked)

    def clear_logs(self):
        '''
        Clear logs from table.
        '''
        self.logs = []
        self.num_of_logs = 0
        self.setWindowTitle(f'Logger ({self.num_of_logs} logs)')
        self.table.setRowCount(0)

    def show_search_box(self):
        '''
        Show search box dialog.
        '''
        # Show the search box and get the search text
        if self.search_box.exec_() == QDialog.Accepted:
            search_text = self.search_box.get_search_text()
            find_next = self.search_box.get_find_next()
            if self.search_in_message(search_text, find_next) is not None:
                self.show_search_box()
            else:
                QMessageBox.information(self, "Search", f"'{search_text}' was not found.")
                self.search_box.reset_search()

    def search_in_message(self, text, find_next=False):
        '''
        Search in message column in the table and put the focus on it.
        '''
        start_row = 0
        if find_next and (self.last_found_item_index is not None):
            start_row = self.last_found_item_index + 1

        for i in range(start_row, self.table.rowCount()):
            item = self.table.item(i, self.log_config.columns.index('Message'))
            if item is None:
                continue
            if text.lower() in item.text().lower():
                self.table.scrollToItem(item)
                self.table.setCurrentItem(item)
                self.last_found_item_index = i
                break
        else:
            # If we didn't find any more items, start from the beginning
            self.last_found_item_index = None
            if start_row != 0:
                self.search_in_message(text)
        return self.last_found_item_index


if __name__ == '__main__':
    # Use argparser to get log file path
    parser = argparse.ArgumentParser()
    parser.add_argument('--log_file', type=str, default='/swgwork/matanl/git/bash_scripts/fw_x86_64.log',
                        help='Path to log file')
    parser.add_argument('--config_file', type=str, default='/swgwork/matanl/git/bash_scripts/config_file.txt',
                        help='Path to log config file')
    args = parser.parse_args()
    log_file_path = args.log_file
    config_file_path = args.config_file

    app = QApplication([])
    logger = Logger(log_file_path, config_file_path)
    logger.show()
    sys.exit(app.exec_())
