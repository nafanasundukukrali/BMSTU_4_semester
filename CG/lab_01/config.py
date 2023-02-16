from PySide6.QtWidgets import QMessageBox


def solve_ls_by_gaus_method(matrix):
    def make_matrix_upper_triangular():
        for k in range(len(matrix)):
            for i in range(k, len(matrix)):
                j = len(matrix[0]) - 1

                while j + 1 > k and abs(matrix[i][k]) > EPSILON:
                    matrix[i][j] /= matrix[i][k]
                    j -= 1

                for i in range(k + 1, len(matrix)):
                    j = len(matrix[0]) - 1

                    while j >= k and abs(matrix[i][k]) > EPSILON:
                        matrix[i][j] -= matrix[k][j]
                        j -= 1

    make_matrix_upper_triangular()

    for i in range(len(matrix), -1, -1):
        for j in range(len(matrix[0]) - 2, i, -1):
            matrix[i][len(matrix[0]) - 1] -= (matrix[j][len(matrix[0]) - 1]
                                              * matrix[i][j])


EPSILON = 1e-8

INPUT_RULES = ("Значения координат должны быть вещестенными числами.\n"
               "Формат ввода:\n"
               "* число в экспоненциальном виде;\n"
               "* между цифрами и знаками отсуствуют пробелы;\n"
               "* между целой и дробной частами точка;")


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
