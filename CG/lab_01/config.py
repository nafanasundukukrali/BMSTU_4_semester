from PySide6.QtWidgets import QMessageBox
from PySide6.QtGui import QColor, Qt

HTMLPATH = "./index.html"


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
                "dot": QColor(255, 105, 180)
            }

    def get_color_shame(self):
        return self._colorShame

    def get_background_settings(self):
        return self._backgroundSettings

    def get_line_styles(self):
        return self._lineStyle


def solve_ls_by_gaus_method(matrix):
    def is_singular():
        for i in range(len(matrix)):
            if not matrix[i][i]:
                return True
        return False

    def bubble_max_row(col):
        max_element = matrix[col][col]
        max_row = col

        for i in range(col + 1, len(matrix)):
            if abs(matrix[i][col]) > abs(max_element) and matrix[i][col] != 0:
                max_element = matrix[i][col]
                max_row = i

        if max_row != col:
            matrix[col], matrix[max_row] = matrix[max_row], matrix[col]

    def solve_gauss():
        n = len(matrix)

        for k in range(n - 1):
            bubble_max_row(k)

            for i in range(k + 1, n):
                div = matrix[i][k] / matrix[k][k]
                matrix[i][-1] -= div * matrix[k][-1]

                for j in range(k, n):
                    matrix[i][j] -= div * matrix[k][j]

        if is_singular():
            return None

        x = [0 for i in range(n)]

        for k in range(n - 1, -1, -1):
            x[k] = (matrix[k][-1] - sum([matrix[k][j] * x[j] for j in range(k + 1, n)])) / matrix[k][k]

        return x

    return solve_gauss()


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
