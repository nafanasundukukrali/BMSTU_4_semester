from PySide6.QtWidgets import QColorDialog, QWidget, QHBoxLayout, QPushButton
from PySide6.QtGui import QColor, QPalette
from PySide6.QtCore import Qt


class ColorDialog(QColorDialog):
    def __init__(self, parent, color):
        super().__init__(parent)
        self.setCurrentColor(color)
        self.setWindowTitle('Выбрать цвет')
        self.show()
        self.exec()


class ColorSelectionField(QWidget):
    default_push_button_text = "Выбрать цвет для "

    def __init__(self, parent,  name, width, action, start_color = QColor(255, 255, 255)):
        super().__init__(parent)
        self._layout = QHBoxLayout()
        self.setLayout(self._layout)

        self._selectButton = QPushButton(name)
        self._selectButton.clicked.connect(self._select_color)
        self._action = action

        self._selectedColor = start_color

        self._colorStatus = QWidget()
        palette = self._colorStatus.palette()
        palette.setColor(self._colorStatus.backgroundRole(), self._selectedColor)
        self._colorStatus.setAutoFillBackground(True)
        self._colorStatus.setPalette(palette)
        self._colorStatus.setFixedWidth(width * 0.2)
        self._colorStatus.setFixedHeight(width * 0.1)

        self._layout.addWidget(self._selectButton)
        self._layout.addWidget(self._colorStatus)

    def _select_color(self):
        dialog = ColorDialog(self, self._selectedColor)
        self._selectedColor = dialog.currentColor()
        palette = self._colorStatus.palette()
        palette.setColor(self._colorStatus.backgroundRole(), self._selectedColor)
        self._colorStatus.setPalette(palette)
        self._action(self._selectedColor)

    def get_color(self):
        return self._selectedColor


