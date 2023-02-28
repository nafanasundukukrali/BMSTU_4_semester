from PySide6.QtWidgets import QMessageBox
from PySide6.QtGui import QColor, Qt


class ThemeTemplate:
    def __init__(self, circle_type):
        self._backgroundSettings = "background-color: white;"

        if circle_type == 1:
            self._lineStyle = Qt.DashDotLine
            self._colorShame = {
                    "center": QColor(200, 0, 0),
                    "circle": QColor(255, 116, 0),
                    "tangent_line": QColor(0, 153, 153),
                    "dot": QColor(0, 204, 0)
                }
        else:
            self._lineStyle = Qt.SolidLine
            self._colorShame = {
                "center": QColor(6, 34, 112),
                "circle": QColor(181, 100, 212),
                "tangent_line": QColor(156, 164, 0),
                "dot": QColor(240, 252, 0)
            }

    def get_color_shame(self):
        return self._colorShame

    def get_background_settings(self):
        return self._backgroundSettings

    def get_line_styles(self):
        return self._lineStyle


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

                if abs(matrix[i][i]) < EPSILON:
                    return None

        return 1

    result = make_matrix_upper_triangular()

    if not result:
        return None

    for i in range(len(matrix), -1, -1):
        for j in range(len(matrix[0]) - 2, i, -1):
            matrix[i][len(matrix[0]) - 1] -= (matrix[j][len(matrix[0]) - 1]
                                              * matrix[i][j])

            matrix[i][j] = 0

    return 1

EPSILON = 1e-4

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
