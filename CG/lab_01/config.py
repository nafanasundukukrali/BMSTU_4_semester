from PySide6.QtWidgets import QMessageBox

EPSILON=1e-8

INPUT_RULES = ("Значения координат должны быть вещестенными числами.\n" 
            "Формат ввода:\n"
            "* число в экспоненциальном виде;\n"
            "* между цифрами и знаками отсуствуют пробелы;\n"
            "* между целой и дробной частами точка;")


class MessageDisplay(QMessageBox):
    def __init__(self, base, messageText, messageHeader="Ошибка",
        messageType="Warning"):
        super().__init__(base)

        if messageHeader:
            self.setWindowTitle(messageHeader)

        if messageType == "Warning":
            self.setWarningMessageIcon()

        self.setText(messageText)
        self.exec()

    def setWarningMessageIcon(self):
        self.setIcon(QMessageBox.Warning)
