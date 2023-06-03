from PySide6.QtWidgets import QMessageBox

TASK = ("Реализовать и исследовать  один из алгоритмов (по заданию преподавателя)  растрового заполнения области.\n"
        "Вариант №9: Алгоритм с упорядоченным списком ребер (лучший вариант).")

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
