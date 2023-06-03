from PySide6.QtWidgets import QWidget, QVBoxLayout, QLabel, QGridLayout, QLineEdit, QHBoxLayout
from PySide6.QtCore import Qt, QPoint


class InputTwoParams(QWidget):
    def __init__(self, parent, title=None, name_1='x', name_2='y', type_data=float):
        super().__init__(parent)
        self._type_data = type_data
        self._base_layout = QVBoxLayout()
        self.setLayout(self._base_layout)

        self._label = QLabel(title)
        self._base_layout.addWidget(self._label)
        self._x = QLineEdit()
        self._y = QLineEdit()
        self._x.setMaximumWidth(170)
        self._y.setMaximumWidth(170)

        h_1 = QHBoxLayout()
        self._base_layout.addLayout(h_1)
        h_1.addStretch()
        h_1.addWidget(QLabel(name_1))
        h_1.addStretch()
        h_1.addWidget(self._x)
        h_1.addStretch()
        h_1.addWidget(QLabel(name_2))
        h_1.addStretch()
        h_1.addWidget(self._y)
        h_1.addStretch()

    def _date_validation(self, value):
        try:
            self._type_data(value)

            if self._type_data == int and int(value) <= 0:
                raise Exception

            return True
        except:
            return False

    def get_data(self):
        if self._date_validation(self._x.text()) and self._date_validation(self._y.text()):
            return QPoint(self._type_data(self._x.text()), self._type_data(self._y.text()))

        return
