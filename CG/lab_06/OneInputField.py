from PySide6.QtWidgets import QWidget, QHBoxLayout, QLabel, QLineEdit
from PySide6.QtCore import Qt


class OneInputField(QWidget):
    def __init__(self, parent, title):
        super().__init__(parent)
        self._base_layout = QHBoxLayout()
        self._base_layout.setAlignment(Qt.AlignmentFlag.AlignJustify)
        self.setLayout(self._base_layout)

        self._label = QLabel(title)
        self._field = QLineEdit()
        self._field.setMaximumWidth(170)

        self._base_layout.addWidget(self._label)
        self._base_layout.addWidget(self._field)

    @staticmethod
    def _date_validation(value):
        try:
            float(value)
            return True
        except:
            return False

    def get_data(self):
        if self._date_validation(self._field.text()):
            return float(self._field.text())

        return