from PySide6.QtWidgets import QMessageBox
from PySide6.QtGui import QColor

TASK = ("Реализовать и исследовать  алгоритм построчного затравочного заполнения.")

class BASE_COLORS:
    fill_color = QColor(255, 0, 0)
    edges_color = QColor(0, 255, 0)
    background_color = QColor(255, 255, 255)

class ERRORS:
    ERROR_MODIFICATION_PARAMS = 1

class MessageDisplay(QMessageBox):
    def __init__(self, base, messageText, messageHeader="Ошибка", messageType="Warning"):
        super().__init__(base)

        if messageHeader:
            self.setWindowTitle(messageHeader)

        if messageType == "Warning":
            self.set_warning_message_icon()

        self.setText(messageText)
        self.exec()

    def set_warning_message_icon(self):
        self.setIcon(QMessageBox.Warning)
