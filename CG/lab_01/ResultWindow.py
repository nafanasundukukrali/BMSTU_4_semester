from PySide6.QtCore import QPoint
from PySide6.QtWidgets import QVBoxLayout, QWidget, QFrame, QTabWidget, QTextBrowser
import copy
import itertools
from PySide6.QtGui import QPainter, QColor, Qt, QPen, QFont
from config import EPSILON, solve_ls_by_gaus_method, ThemeTemplate, HTMLPATH, MessageDisplay

class Circles:
    SUCCESS = 0
    ALL_DOT_SAME = 2
    LESS_DATA = 3
    NO_RESULT = 4

    def __init__(self, first_data_array, second_data_array):
        self._answer = Circles.SUCCESS
        self._first_data_array = self._remove_duplicates(first_data_array, self._comparatorSameCoords)
        self._second_data_array = self._remove_duplicates(second_data_array, self._comparatorSameCoords)
        self._circles_paires = []
        
        if not self._first_data_array or not second_data_array and first_data_array and second_data_array:
            self._answer = Circles.ALL_DOT_SAME
        elif len(self._first_data_array) + len(self._second_data_array) < 5:
            self._answer = Circles.LESS_DATA
        else:
            self._analysData()
            
            if not self._circles_paires:
                self._answer = Circles.NO_RESULT

    def get_answer(self):
        return self._answer

    def get_circles_pairs(self):
        return self._circles_paires

    def _remove_duplicates(self, array, compareFunction):
        result = []

        for i in range(len(array)):
            j = 0
            
            while j < i and not compareFunction(array[i], array[j]):
                j += 1

            if i == j:
                result.append(array[j])

        array = copy.deepcopy(result)

        if not array:
            self._answer = Circles.LESS_DATA

        return array

    @staticmethod
    def _comparatorSameCircles(circle1, circle2):
        return (abs(circle1[0][0] - circle2[0][0]) < EPSILON and abs(circle1[0][1] - circle2[0][1]) < EPSILON and
                abs(circle1[1] - circle2[1]) < EPSILON)

    def _get_circles_from_three_dot(self, array):
        circles_coords_by_tree_dots = list(itertools.combinations(array, 3))
        circles_by_center_and_r = []

        for circle_data in circles_coords_by_tree_dots:
            result = self._getCirclesParamsFromThreeDots(*circle_data)

            if result:
                circles_by_center_and_r.append(result)

        if circles_by_center_and_r:
            circles_by_center_and_r = self._remove_duplicates(circles_by_center_and_r, self._comparatorSameCircles)

        return circles_by_center_and_r

    def _analysData(self): 
        def get_compare_params(circle_data):
            x_left = circle_data[0][0] - circle_data[1]
            x_right = circle_data[0][0] + circle_data[1]
            y = circle_data[0][1]
            
            return {'radius': circle_data[1], 
                    'x_left': x_left,
                    'x_right': x_right,
                    'y': y}

        first_circles_by_center_and_r = self._get_circles_from_three_dot(self._first_data_array)
        second_circles_by_center_and_r = self._get_circles_from_three_dot(self._second_data_array)

        if not first_circles_by_center_and_r or not second_circles_by_center_and_r:
            self._answer = self.NO_RESULT

        if first_circles_by_center_and_r and second_circles_by_center_and_r:
            for i in range(len(first_circles_by_center_and_r)):
                circle1_data = get_compare_params(first_circles_by_center_and_r[i])

                for j in range(len(second_circles_by_center_and_r)):
                    circle2_data = get_compare_params(second_circles_by_center_and_r[j])
                    centers_distance = self._getCutLengthByCoords(first_circles_by_center_and_r[i][0],
                                                                  second_circles_by_center_and_r[j][0])

                    if ((centers_distance >= abs(circle1_data['radius'] +
                                               circle2_data['radius'])) and
                        (abs(circle1_data['x_left'] - circle2_data['x_right']) < EPSILON or
                         abs(circle1_data['x_right'] - circle2_data['x_left']) < EPSILON)):
                        self._circles_paires.append([first_circles_by_center_and_r[i],
                                                     second_circles_by_center_and_r[j]])
    
    @staticmethod
    def _getCutLengthByCoords(dot1, dot2):
        return ((dot1[0] - dot2[0])**2 + (dot1[1] - dot2[1])**2)**0.5 

    def _getCirclesParamsFromThreeDots(self, dot1, dot2, dot3):

        coord_matrix_for_center = [[2 * (dot2[0] - dot1[0]), 2 * (dot2[1] - dot1[1]),
                                    dot2[0] ** 2 - dot1[0] ** 2 + dot2[1] ** 2 - dot1[1] ** 2],
                                   [2 * (dot3[0] - dot2[0]), 2 * (dot3[1] - dot2[1]),
                                    dot3[0] ** 2 - dot2[0] ** 2 + dot3[1] ** 2 - dot2[1] ** 2]]

        result = solve_ls_by_gaus_method(coord_matrix_for_center)

        if not result:
            return []

        return [[result[0], result[1]], self._getCutLengthByCoords(dot1, [result[0], result[1]]), dot1, dot2, dot3]

    @staticmethod
    def _comparatorSameCoords(coords1, coords2):
        return coords1[0] == coords2[0] and coords1[1] == coords2[1]


class PaintField(QFrame):
    def __init__(self, parent, windowParams, circlesPairs):
        super().__init__(parent)
        self._kx = parent.kx
        self._ky = parent.ky
        self._xm = parent.xm
        self._ym = parent.ym
        self._labelFont = QFont("Times", 15, QFont.Bold)
        self.setFixedSize(*windowParams)

        theme1 = ThemeTemplate(1)
        theme2 = ThemeTemplate(2)

        self._firstCirclesTheme = theme1
        self._secondCirclesTheme = theme2

        self.setStyleSheet(theme1.get_background_settings())
        self._circlesPairs = circlesPairs
    
    def paintEvent(self, event):
        super().paintEvent(event)
        self._painter = QPainter(self)
        self._painter.setFont(self._labelFont)
        # self._draw_coordinate_axes()
        self._drawCircles()
        self._painter.end()

    def _drawOneCircle(self, theme, circle, pen):
        center = QPoint(*self._zoom_and_move_cords(*circle[0]))

        pen.setWidth(5)
        pen.setColor(theme.get_color_shame()['center'])
        self._painter.setPen(pen)

        self._painter.drawPoint(center)

        pen.setWidth(2)
        pen.setColor(theme.get_color_shame()['circle'])
        self._painter.setPen(pen)

        self._painter.drawEllipse(center, circle[1] * self._kx, circle[1] * self._ky)

        for dot in circle[2:]:
            cords = QPoint(*self._zoom_and_move_cords(*dot[:len(dot) - 1]))

            pen.setWidth(5)
            pen.setColor(theme.get_color_shame()['dot'])
            self._painter.setPen(pen)
            self._painter.drawPoint(cords)

            pen.setWidth(2)
            pen.setColor(QColor(0, 0, 0))
            self._painter.setPen(pen)
            self._painter.drawText(cords, f'{dot[2]}:({dot[0]};{dot[1]})')

    def _drawCircles(self):
        pen = QPen()

        for pair in self._circlesPairs:
            self._drawOneCircle(self._firstCirclesTheme, pair[0], pen)
            self._drawOneCircle(self._secondCirclesTheme, pair[1], pen)

            pen.setWidth(2)
            pen.setColor(self._firstCirclesTheme.get_color_shame()['tangent_line'])

            self._painter.setPen(pen)

            if (abs(pair[0][0][0] + pair[0][1] - (pair[1][0][0] - pair[1][1]))) < EPSILON:
                self._painter.drawLine(QPoint(self._zoom_and_move_cords(pair[0][0][0] + pair[0][1], 0)[0], 0),
                                       QPoint(self._zoom_and_move_cords(pair[1][0][0] - pair[1][1], 0)[0],
                                              self.height()))
            else:
                self._painter.drawLine(QPoint(self._zoom_and_move_cords(pair[0][0][0] - pair[0][1], 0)[0], 0),
                                       QPoint(self._zoom_and_move_cords(pair[1][0][0] + pair[1][1], 0)[0],
                                              self.height()))

    def _zoom_and_move_cords(self, x, y):
        x = self._kx * x + self._xm
        y = self.height() - (self._ky * y + self._ym)

        return [x, y]


class InstructionWidget(QWidget):
    def __init__(self, parent):
        super().__init__(parent)

        self.setFixedSize(parent.size())

        htmlstring = ""

        with open(HTMLPATH, "r") as file:
            htmlstring = '\n'.join(file.readlines())

        self._w = QTextBrowser()
        self._w.setOpenExternalLinks(True)
        self._w.setHtml(htmlstring)
        self._layout = QVBoxLayout()
        self._layout.addWidget(self._w)
        self.setLayout(self._layout)


class ResultWindow(QWidget):

    WINDOW_SIZE_COEF = 0.9
    PAINT_FIELD_HEIGHT_COEF = 0.96
    ARROW_WIDTH = 30

    def __init__(self, parent, firstData, secondData, screenParams):
        super().__init__()
        self.setFixedSize(screenParams.width() * self.WINDOW_SIZE_COEF,
                          screenParams.height() * self.WINDOW_SIZE_COEF)
        self.kx = 0
        self.ky = 0
        self.xm = 0
        self.ym = 0

        self._resultInfo = ""
        circles = Circles(firstData, secondData)
        self._circlesPairs = []

        if circles.get_answer() == Circles.LESS_DATA:
            MessageDisplay(parent, "Присутствуют только вырожденные случаи.")
        elif circles.get_answer() == Circles.NO_RESULT:
            MessageDisplay(parent, "Нет решений.")
        elif circles.get_answer() == Circles.SUCCESS:
            self._circlesPairs = circles.get_circles_pairs()
            self._display_result()
        else:
            MessageDisplay(parent, "Нет решений.")

    def _display_result(self):
        self._get_zoom_coefficients()
        self._paintField = PaintField(self,
                                      [self.width(), self.height() * self.PAINT_FIELD_HEIGHT_COEF],
                                      self._circlesPairs)

        self._mainLayout = QTabWidget(self)
        self._mainLayout.addTab(self._paintField, "Результат")
        self._mainLayout.setFixedWidth(self.width())
        self._mainLayout.setFixedHeight(self.height())
        self._mainLayout.addTab(InstructionWidget(self), "Легенда к графику и ход решения")

        self.initGUI()
    
    def _get_zoom_coefficients(self):
        circle1 = self._circlesPairs[0][0]
        max_right = circle1[0][0] + circle1[1]
        max_left = circle1[0][0] - circle1[1]
        max_bottom = circle1[0][1] - circle1[1]
        max_top = circle1[0][1] + circle1[1]

        for circlesPair in self._circlesPairs:
            for circle in circlesPair:
                max_right = max(circle[0][0] + circle[1], max_right)
                max_left = min(circle[0][0] - circle[1], max_left)
                max_bottom = min(circle[0][1] - circle[1], max_bottom)
                max_top = max(circle[0][1] + circle[1], max_top)

        height = self.height() * self.PAINT_FIELD_HEIGHT_COEF - self.ARROW_WIDTH * 2

        real_width = abs(max_right - max_left)
        real_height = abs(max_top - max_bottom)
        
        self.ky = height / real_height
        self.kx = (self.width() - 2 * self.ARROW_WIDTH) / real_width

        self.kx = min(self.kx, self.ky)

        self.ky = self.kx

        self.xm = -self.kx * max_left + self.kx / self.kx * self.ARROW_WIDTH
        self.ym = -self.ky * max_bottom + self.ky / self.ky * self.ARROW_WIDTH

    def initGUI(self):
        self.show()
