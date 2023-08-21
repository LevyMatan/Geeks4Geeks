from PyQt5.QtWidgets import QApplication, QMainWindow, QTableWidget, QTableWidgetItem, QHeaderView, QCheckBox, QVBoxLayout, QHBoxLayout, QWidget, QLabel
from PyQt5.QtCore import Qt, QTimer
import sys
import time

class LogConfig:
    def __init__(self, config_file_path):
        self.ignored_columns_filters = ["Time Stamp", "Line", "Message"]
        self.columns = []
        self.seperator_char = ','
        with open(config_file_path, 'r') as f:
            for line in f.readlines():
                line = line.strip()
                if line.startswith('seperator'):
                    self.seperator_char = line.split('=')[1].strip()
                elif line.startswith('columns'):
                    self.columns = [column.strip() for column in line.split('=')[1].split(self.seperator_char)]

    def __getitem__(self, index):
        return self.columns[index]
    def __len__(self):
        return len(self.columns)
    def __str__(self) -> str:
        return_str = 'Log Config:\n'
        return_str += f'seperator = {self.seperator_char}\n'
        return_str += f'columns=\n'
        for ind, column in enumerate(self.columns):
            return_str += f'\t{ind}) {column}\n'
        return return_str

class Logger(QMainWindow):
    def __init__(self, log_file, log_config_path):
        super().__init__()
        self.log_file = log_file
        # Initialize UI
        self.setWindowTitle('Logger')
        self.table = QTableWidget()
        self.setCentralWidget(self.table)
        self.log_config = LogConfig(log_config_path)
        print(self.log_config)
        self.filters = {}
        self.seperator_char = self.log_config.seperator_char
        self.num_of_logs = 0
        self.log_file_pos = 0
        self.logs = []

        # Load logs from file
        self.updateLogs()

        # Set up table display
        self.table.setColumnCount(len(self.log_config))
        self.table.setHorizontalHeaderLabels(self.log_config.columns)
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.verticalHeader().setVisible(False)
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)
        self.table.setSelectionBehavior(QTableWidget.SelectRows)
        self.table.setSelectionMode(QTableWidget.SingleSelection)

        # They are two hierarchies of filters:
        # 1. Filter by which column to filter
        # 2. Filter by which value to filter

        # Initialize filters
        self.initializeFilters()

        # Start timer to update logs
        self.timer = QTimer()
        self.timer.timeout.connect(self.updateLogs)
        self.timer.start(1000)

    def initializeSidebar(self):
        # Create sidebar
        self.sidebar = QWidget()
        self.sidebar_layout = QVBoxLayout()
        self.sidebar.setLayout(self.sidebar_layout)
        self.sidebar.setFixedWidth(200)
        self.sidebar.setContentsMargins(0, 0, 0, 0)
        self.sidebar.setStyleSheet('background-color: #1e1e1e; border-right: 1px solid #d0d0d0;')
        self.sidebar_label = QLabel('Filters')
        self.sidebar_label.setAlignment(Qt.AlignCenter)
        self.sidebar_label.setStyleSheet('font-weight: bold;')
        self.sidebar_layout.addWidget(self.sidebar_label)

    def updateSidebar(self):
        # self.sidebar.deleteLater()
        self.initializeSidebar()
        time.sleep(2.1)
        print("updateSidebar")
        # for j, column in enumerate(self.log_config.columns):
        #     checkbox = self.columns_filters[column]
        #     self.sidebar_layout.addWidget(checkbox)

        # for column, filter_dict in self.filters.items():
        #     if not self.columns_filters[column].isChecked():
        #         continue
        #     column_label = QLabel(column)
        #     column_label.setStyleSheet('font-weight: bold;')
        #     self.sidebar_layout.addWidget(column_label)
        #     for value, checkbox in filter_dict.items():
        #         self.sidebar_layout.addWidget(checkbox)

    def initializeFilters(self):

        # Create sidebar
        self.initializeSidebar()

        # Choose by which column to create a filter
        self.columns_filters = {}
        for j, column in enumerate(self.log_config.columns):
            checkbox = QCheckBox(column)
            checkbox.setChecked(True)
            if column in self.log_config.ignored_columns_filters:
                checkbox.setChecked(False)
            checkbox.stateChanged.connect(self.filterLogs)
            self.columns_filters[column] = checkbox
            self.sidebar_layout.addWidget(checkbox)

        # Add filter checkboxes
        for j, column in enumerate(self.log_config.columns):
            if self.columns_filters[column].isChecked():
                values = set([log[j] for log in self.logs])
                self.filters[column] = {}
                for value in values:
                    checkbox.setStyleSheet('background-color: #1e1e1e;')
                    checkbox = QCheckBox(value)
                    checkbox.setChecked(True)
                    checkbox.stateChanged.connect(self.filterLogs)
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
        self.main_widget = QWidget()
        self.main_layout = QHBoxLayout()
        self.main_layout.addWidget(self.table)
        self.main_layout.addWidget(self.sidebar)
        self.main_widget.setLayout(self.main_layout)
        self.setCentralWidget(self.main_widget)

    def updateLogs(self):
        # Load new logs from file
        # read only from last file end position
        with open(self.log_file, 'r') as f:
            # Move to last file end position
            f.seek(self.log_file_pos, 0)
            # Read new logs
            new_logs = f.readlines()
            # Save end of file position
            self.log_file_pos = f.tell()
        new_logs = [log.strip().split(self.seperator_char) for log in new_logs]
        self.logs += new_logs

        # Display number of logs on window title
        self.num_of_logs += len(new_logs)
        self.setWindowTitle(f'Logger ({self.num_of_logs} logs)')

        # Update table display
        self.table.setRowCount(len(self.logs))
        for i, log in enumerate(self.logs):
            for j, column in enumerate(self.log_config.columns):
                item = QTableWidgetItem(log[j])
                self.table.setItem(i, j, item)
            if self.filters:
                self.applyFilters(i, log)
        # Scroll to bottom if user is not looking at a specific part of the logger
        if self.table.verticalScrollBar().value() == self.table.verticalScrollBar().maximum():
            self.table.scrollToBottom()

    def applyFilters(self, i, log):
        visible = True
        for j, column in enumerate(self.log_config):
            if not self.columns_filters[column].isChecked():
                continue
            checkbox = self.filters[column][log[j]]
            if not checkbox.isChecked():
                visible = False
        self.table.setRowHidden(i, not visible)

    def filterLogs(self):
        # Filter logs based on checkbox selection
        for i, log in enumerate(self.logs):
            self.applyFilters(i, log)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    logger = Logger('log.txt', "config_file.txt")
    logger.show()
    sys.exit(app.exec_())