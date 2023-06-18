from PySide6.QtWidgets import QMessageBox
from PySide6.QtGui import QColor

TASK = ("Реализация алгоритма отсечения отрезка регулярным отсекателем. Вариант №9: Алгоритм разбиения отрезка средней точкой.")

class BASE_COLORS:
    splitter_color = QColor(255, 0, 0)
    line_color = QColor(0, 255, 0)
    result_color = QColor(0, 0, 255)
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
