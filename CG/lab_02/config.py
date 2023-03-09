from PySide6.QtWidgets import QMessageBox

TASK = "Задание: Нарисовать исходный рисунок, осуществить его перенос, масштабирование и поворот."
class ERRORS:
    ERROR_MODIFICATION_PARAMS = 1

EPSILON = 0.5

BASE_WIDTH = 100
WHEELS_WIDTH = 200
WHEELS_HEIGHT = 70
BASE_HEIGHT = 50
MAIN_ELLIPSE_HEIGHT = 30
SMALL_ELLIPSE_WIDTH = 50
TUBE_HEIGHT = 40

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
