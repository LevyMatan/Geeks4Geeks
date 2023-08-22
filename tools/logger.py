'''
logger.py is a tool that displays logs in a table format.
It reads logs from a file and displays them in a table.
It also allows the user to filter the logs by column and value.
'''
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QTableWidget, QTableWidgetItem
from PyQt5.QtWidgets import QHeaderView, QCheckBox, QVBoxLayout, QHBoxLayout, QWidget, QLabel
from PyQt5.QtWidgets import QLineEdit, QScrollArea, QPushButton, QColorDialog, QSplitter
from PyQt5.QtGui import QColor
from PyQt5.QtCore import QTimer, Qt

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

    def __init__(self, log_file, log_config_path):
        super().__init__()
        self.resize(1000, 600)
        self.log_file = log_file

        # Initialize UI
        self.setWindowTitle('Logger')
        self.table = QTableWidget()
        self.sidebar = QWidget()
        self.scroll_area = QScrollArea()

        # Initialize Variables
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
            'background-color: #76B900; border-right: 1px solid #d0d0d0;')

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
            if column in self.log_config.ignored_columns_filters:
                checkbox.setChecked(False)
            checkbox.stateChanged.connect(self.filter_logs)
            self.columns_filters[column] = checkbox
            self.sidebar.layout().addWidget(checkbox)

        # Add filter checkboxes
        for j, column in enumerate(self.log_config.columns):
            if column in self.log_config.ignored_columns_filters:
                continue
            if self.columns_filters[column].isChecked():
                values = {log[j] for log in self.logs}
                self.filters[column] = {}
                for value in values:
                    checkbox = QCheckBox(value)
                    checkbox.setChecked(True)
                    checkbox.stateChanged.connect(self.filter_logs)
                    self.filters[column][value] = checkbox

        for column, filter_dict in self.filters.items():
            if not self.columns_filters[column].isChecked():
                continue
            column_label = QLabel(column)
            column_label.setStyleSheet('font-weight: bold;')
            self.sidebar.layout().addWidget(column_label)
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

    def clear_logs(self):
        '''
        Clear logs from table.
        '''
        self.logs = []
        self.num_of_logs = 0
        self.setWindowTitle(f'Logger ({self.num_of_logs} logs)')
        self.table.setRowCount(0)

if __name__ == '__main__':
    app = QApplication([])
    logger = Logger('log.txt', "config_file.txt")
    logger.show()
    sys.exit(app.exec_())
