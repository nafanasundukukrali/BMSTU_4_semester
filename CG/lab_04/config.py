from PySide6.QtWidgets import QMessageBox

TASK = "Реализовать алгоритмы ЦДА, Брезенхема (действительный, целочисленный, с устранением ступенчатости), By."

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
