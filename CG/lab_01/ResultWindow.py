from PySide6.QtCore import QPoint
from PySide6.QtWidgets import QLabel, QStyle, QVBoxLayout, QWidget, QFrame, QTabWidget, QFileDialog
import copy
import itertools
from PySide6.QtGui import QPainter, QColor, QBrush, QPalette, Qt, QPen, QFont
from config import EPSILON, solve_ls_by_gaus_method, ThemeTemplate
from PySide6 import QtWebEngineWidgets, QtCore

class Circles:
    SUCCESS = 0
    ALL_DOT_SAME = 2
    LESS_DATA = 3
    NO_RESULT = 4

    def __init__(self, array):
        self.answer = Circles.SUCCESS
        # self.array = []
        self.array = self._removeDuplicates(array, self._comparatorSameCoords)
        self.circles_paires = []
        
        if not self.array and array:
            self.answer = Circles.ALL_DOT_SAME
        elif len(self.array) < 5:
            self.answer = Circles.LESS_DATA
        else:
            self._analysData()
            
            if not self.circles_paires:
                self.answer = Circles.NO_RESULT
        

    def _removeDuplicates(self, array, compareFunction):
        result = []

        for i in range(len(array)):
            j = 0
            
            while j < i and not compareFunction(array[i], array[j]):
                j += 1

            if i == j:
                result.append(array[j])

        array = copy.deepcopy(result)

        if not array:
            self.answer = Circles.LESS_DATA

        return array

    @staticmethod
    def _comparatorSameCircles(circle1, circle2):
        return (abs(circle1[0][0] - circle2[0][0]) < EPSILON and abs(circle1[0][1] - circle2[0][1]) < EPSILON and
                abs(circle1[1] - circle2[1]) < EPSILON)

    def _analysData(self): 
        def get_compare_params(circle_data):
            x_left = circle_data[0][0] - circle_data[1]
            x_right = circle_data[0][0] + circle_data[1]
            y = circle_data[0][1]
            
            return {'radius': circle_data[1], 
                    'x_left': x_left,
                    'x_right': x_right,
                    'y': y}

        all_circles_coords_by_tree_dots = list(itertools.combinations(self.array, 3))
        all_circles_by_center_and_r = []

        for circle_data in all_circles_coords_by_tree_dots:
            result = self._getCirclesParamsFromThreeDots(*circle_data)

            if result:
                all_circles_by_center_and_r.append(result)

        if not all_circles_by_center_and_r:
            self.answer = self.NO_RESULT

        all_circles_by_center_and_r = self._removeDuplicates(all_circles_by_center_and_r, self._comparatorSameCircles)

        for i in range(len(all_circles_by_center_and_r)):
            circle1_data = get_compare_params(all_circles_by_center_and_r[i])

            for j in range(i + 1, len(all_circles_by_center_and_r)):
                circle2_data = get_compare_params(all_circles_by_center_and_r[j])
                centers_distance = self._getCutLengthByCoords(all_circles_by_center_and_r[i][0],
                                                              all_circles_by_center_and_r[j][0])

                if ((centers_distance >= abs(circle1_data['radius'] + 
                                           circle2_data['radius'])) and 
                    (abs(circle1_data['x_left'] - circle2_data['x_right']) < EPSILON or
                     abs(circle1_data['x_right'] - circle2_data['x_left']) < EPSILON)):
                    self.circles_paires.append([all_circles_by_center_and_r[i],
                                                all_circles_by_center_and_r[j]])
    
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

        return [[coord_matrix_for_center[0][-1],
                 coord_matrix_for_center[1][-1]], self._getCutLengthByCoords(dot1, [coord_matrix_for_center[0][-1],
                 coord_matrix_for_center[1][-1]]), dot1, dot2, dot3]

    @staticmethod
    def _comparatorSameCoords(coords1, coords2):
        return coords1[0] == coords2[0] and coords1[1] == coords2[1]


class PaintField(QFrame):
    def __init__(self, parent, windowParams, firstCirclesPairs, secondCirclesPairs):
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
        self._firstCirclesPairs = firstCirclesPairs
        self._secondCirclesPairs = secondCirclesPairs

    
    def paintEvent(self, event):
        super().paintEvent(event)
        self._painter = QPainter(self)
        self._painter.setFont(self._labelFont)
        self._draw_coordinate_axes()
        self._drawCircles(self._firstCirclesPairs, self._firstCirclesTheme)
        self._drawCircles(self._secondCirclesPairs, self._secondCirclesTheme)
        self._painter.end()

    def _drawCircles(self, array, theme):
        pen = QPen()

        for pair in array:
            pen.setStyle(theme.get_line_styles())

            for circle in pair:
                center = QPoint(*self._zoom_and_move_cords(*circle[0]))

                pen.setWidth(5)
                pen.setColor(theme.get_color_shame()['center'])
                self._painter.setPen(pen)

                self._painter.drawPoint(center)

                pen.setWidth(2)
                pen.setColor(theme.get_color_shame()['circle'])
                self._painter.setPen(pen)

                self._painter.drawEllipse(center, circle[1] * self._kx, circle[1] * self._ky)

                pen.setWidth(5)
                pen.setColor(theme.get_color_shame()['dot'])
                self._painter.setPen(pen)

                for dot in circle[2:]:
                    cords = QPoint(*self._zoom_and_move_cords(*dot))
                    self._painter.drawPoint(cords)

            pen.setWidth(1)
            pen.setColor(theme.get_color_shame()['tangent_line'])
            pen.setStyle(Qt.SolidLine)

            self._painter.setPen(pen)

            if (abs(pair[0][0][0] + pair[0][1] - (pair[1][0][0] - pair[1][1]))) < EPSILON:
                self._painter.drawLine(QPoint(self._zoom_and_move_cords(pair[0][0][0] + pair[0][1], 0)[0], 0),
                                       QPoint(self._zoom_and_move_cords(pair[1][0][0] - pair[1][1], 0)[0],
                                              self.height()))
            else:
                self._painter.drawLine(QPoint(self._zoom_and_move_cords(pair[0][0][0] - pair[0][1], 0)[0], 0),
                                       QPoint(self._zoom_and_move_cords(pair[1][0][0] + pair[1][1], 0)[0],
                                              self.height()))

    def _draw_coordinate_axes(self):
        pen = QPen()
        pen.setColor(QColor(0, 0, 0))
        pen.setStyle(Qt.SolidLine)
        pen.setWidth(2)

        self._painter.setPen(pen)

        self._painter.drawLine(QPoint(self._xm, 0),
                               QPoint(self._xm, self.height()))
        self._painter.drawLine(QPoint(0, self.height() - self._ym),
                               QPoint(self.width(), self.height() - self._ym))

        self._painter.drawLine(self._xm, 0, self._xm + 10, 10)
        self._painter.drawLine(self._xm, 0, self._xm - 10, 10)

        self._painter.drawLine(self.width(), self.height() - self._ym, self.width() - 10, self.height() - self._ym - 10)
        self._painter.drawLine(self.width(), self.height() - self._ym, self.width() - 10, self.height() - self._ym + 10)

        x_pos = self._xm + 15 if self._xm + 15 < self.width() else self._xm - 15
        y_pos = self._ym + 15 if self._ym + 15 < self.height() else self._ym - 15

        self._painter.drawText(x_pos, 15, "y")
        self._painter.drawText(self.width() - 15, self.height() - y_pos, "x")

    def _zoom_and_move_cords(self, x, y):
        x = self._kx * x + self._xm
        y = self.height() - (self._ky * y + self._ym)

        return [x, y]


class InstructionWidget(QWidget):
    def __init__(self, parent):
        super().__init__(parent)

        self._textLabel_ = QLabel("")
        self._textLabel_.setStyleSheet("color: pink")
        self._layout = QVBoxLayout()
        self._layout.addWidget(self._textLabel_)
        self.setLayout(self._layout)
        self.setFixedWidth(parent.width())
        self.setFixedHeight(parent.height())
        # filename, _ = QFileDialog.getOpenFileName(self, "./index.html")
        #
        # if filename:
        #     with open(filename, 'r') as f:
        #         html = f.read()
        #
        # self.w = QtWebEngineWidgets.QWebEngineView()
        # self.w.load("./index.html")

class ResultWindow(QWidget):

    WINDOW_SIZE_COEF = 0.9
    PAINT_FIELD_HEIGHT_COEF = 0.8
    ARROW_WIDTH = 10

    def __init__(self, firstData, secondData, screenParams):
        super().__init__()
        self.setFixedSize(screenParams.width() * self.WINDOW_SIZE_COEF,
                          screenParams.height() * self.WINDOW_SIZE_COEF)
        self.kx = 0
        self.ky = 0
        self.xm = 0
        self.ym = 0

        self._resultInfo = ""
        self._firstCirclesPairs = Circles(firstData).circles_paires
        self._secondCirclesPairs = Circles(secondData).circles_paires

        self._get_zoom_coefficients()
        self._paintField = PaintField(self,
                                      [self.width(), self.height() * self.PAINT_FIELD_HEIGHT_COEF],
                                      self._firstCirclesPairs, self._secondCirclesPairs)

        self._mainLayout = QTabWidget(self)
        self._mainLayout.addTab(self._paintField, "Результат")
        self._mainLayout.setFixedWidth(self.width())
        self._mainLayout.setFixedHeight(self.height())
        self._mainLayout.addTab(InstructionWidget(self), "Инструкция и ход решения")

        self.initGUI()
    
    def _get_zoom_coefficients(self):
        circle1 = self._firstCirclesPairs[0][0]
        max_right = circle1[0][0] + circle1[1]
        max_left = circle1[0][0] - circle1[1]
        max_bottom = circle1[0][1] - circle1[1]
        max_top = circle1[0][1] + circle1[1]

        for circlesPair in self._firstCirclesPairs + self._secondCirclesPairs:
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
