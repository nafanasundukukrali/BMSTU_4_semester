from PySide6.QtWidgets import QListWidget, QWidget, QPushButton, QVBoxLayout
from PySide6.QtGui import QColor
from AlgorithmFunctions import AlgorithmFunctions


class AlgorithmSelectionField(QWidget):
    def __init__(self, parent):
        super().__init__(parent)
        self._list_layout = QListWidget()
        self._layout = QVBoxLayout()
        self.setLayout(self._layout)
        self._layout.addWidget(self._list_layout)
        self._algorithms = AlgorithmFunctions().get_algorithms_list()

        for algorithm_type in list(self._algorithms.keys()):
            self._list_layout.addItem(algorithm_type)

        self._list_layout.item(0).setSelected(True)

    def get_selected_algorithm_type(self):
        return self._algorithms[self._list_layout.currentItem().text()]



