from PySide6.QtWidgets import QHBoxLayout, QWidget, QLineEdit, QLabel


class SpaceAndCountSelection(QWidget):
    def __init__(self, parent):
        super().__init__(parent)
        layout = QHBoxLayout()
        self._b_1 = QRadioButton(name_1)
        self._b_1.setChecked(True)
        layout.addWidget(self._b_1)
        self._b_2 = QRadioButton(name_2)
        layout.addWidget(self._b_2)
        self.setLayout(layout)

    def get_type(self):
        if self._b_1.isChecked():
            return 0

        return 1
