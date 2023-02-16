from PySide6.QtCore import QPoint
from PySide6.QtWidgets import QLabel, QStyle, QVBoxLayout, QWidget, QFrame, QSizePolicy
import copy
import itertools
from PySide6.QtGui import QPainter, QColor, QBrush, QPalette, Qt, QPen
from config import EPSILON, solve_ls_by_gaus_method

class Circles:
    SUCCESS = 0
    ALL_DOT_SAME = 2
    LESS_DATA = 3
    NO_RESULT = 4

    def __init__(self, array):
        self.answer = Circles.SUCCESS
        self.array = []
        self._removeDuplicates(array, self._comparatorSameCoords)
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

        self.array = copy.deepcopy(result)

        if not self.array:
            self.answer = Circles.LESS_DATA


    @staticmethod
    def _comparatorSameCircles(circle1, circle2):
        return (circle1[0][0] == circle2[0][0] and circle1[0][1] ==
                circle2[0][1] and circle1[1] == circle2[1])

    def _analysData(self): 
        def get_compare_params(circle_data):
            x_left = circle_data[i][0][0] - circle_data[1]
            x_right = circle_data[i][0][0] + circle_data[1]
            y = circle_data[i][0][1]
            
            return {'radius': circle_data[1], 
                    'x_left': x_left,
                    'x_right': x_right,
                    'y': y}

        all_circles_coords_by_tree_dots = list(itertools.permutations(self.array, 3))
        all_circles_by_center_and_r = [
                self._getCirclesParamsFromThreeDots(*circle_data) for
                                       circle_data in
                                       all_circles_coords_by_tree_dots]

        self._removeDuplicates(all_circles_by_center_and_r, self._comparatorSameCircles)

        for i in range(len(all_circles_by_center_and_r)):
            circle1_data = get_compare_params(all_circles_by_center_and_r[i])

            for j in range(i + 1, len(all_circles_by_center_and_r)):
                circle2_data = get_compare_params(all_circles_by_center_and_r[j])
                centers_distance = self._getCutLengthByCoords(all_circles_by_center_and_r[i][0],
                                                              all_circles_by_center_and_r[j][0])

                if ((centers_distance >= abs(circle1_data['radius'] + 
                                           circle2_data['radius'])) and 
                    (circle1_data['x_left'] == circle2_data['x_right'] or
                     circle1_data['x_right'] == circle2_data['x_left'])):
                        self.circles_paires.append([all_circles_by_center_and_r[i],
                                                    all_circles_by_center_and_r[j]])
    
    @staticmethod
    def _getCutLengthByCoords(dot1, dot2):
        return ((dot1[0] - dot2[0])**2 + (dot1[1] - dot2[1])**2)**0.5 

    def _getCirclesParamsFromThreeDots(self, dot1, dot2, dot3):
        def getSbyHeronsFormula(a, b, c):
            half_p = (a+b+c)/2

            return (half_p * (half_p - a) * (half_p - b) * (half_p - c))**0.5


                
        a = self._getCutLengthByCoords(dot1, dot2)
        b = self._getCutLengthByCoords(dot2, dot3)
        c = self._getCutLengthByCoords(dot1, dot3)

        S_triangle_in_circle = getSbyHeronsFormula(a, b, c)
        R_circle = (a * b * c) / 4 / S_triangle_in_circle

        coord_x_of_middle_dot = (dot1[0] + dot2[0]) / 2
        coord_y_of_middle_dot = (dot1[1] + dot2[1]) / 2
        
        coord_matrix_for_center = [[ dot2[0] - coord_x_of_middle_dot, dot2[1] - coord_y_of_middle_dot,
                                    coord_x_of_middle_dot * dot2[0] -
                                    coord_x_of_middle_dot ** 2 +
                                    coord_y_of_middle_dot * dot2[1] -
                                    coord_y_of_middle_dot ** 2],
                                   [ dot1[0] - coord_x_of_middle_dot, dot1[1] - coord_y_of_middle_dot,
                                    coord_x_of_middle_dot * dot1[0] -
                                    coord_x_of_middle_dot ** 2 +
                                    coord_y_of_middle_dot * dot1[1] -
                                    coord_x_of_middle_dot ** 2]]

        solve_ls_by_gaus_method(coord_matrix_for_center)

        return [[coord_matrix_for_center[0][-1],
                 coord_matrix_for_center[1][-1]], R_circle]

    @staticmethod
    def _comparatorSameCoords(coords1, coords2):
        return coords1[0] == coords2[0] and coords1[1] == coords2[1]

class PaintField(QFrame):
    PAINT_FIELD_HEIGHT_COEF = 0.8 

    def __init__(self, parent, firstCirclesPairs, secondCirclesPairs):
        super().__init__(parent)
        self._kx = parent.kx
        self._ky = parent.ky
        self._xm = parent.xm
        self._ym = parent.ym

        self.setFixedSize(parent.width(), parent.height() * self.PAINT_FIELD_HEIGHT_COEF)
        self._firstColor = [QColor(200, 0, 0), QColor(255,105,180), QColor(0,191,255)]
        self._firstDrawStyle = Qt.DashDotLine
        self._secondColor = [QColor(255, 80, 0, 160), QColor(0,255,255), QColor(210,105,30)]
        self.setStyleSheet("background-color: white;")
        self._firstCirclesPairs = firstCirclesPairs
        self._secondCirclesPairs = secondCirclesPairs

    
    def paintEvent(self, event):
        super().paintEvent(event)
        self._painter = QPainter(self)
        self._drawCircles(self._firstCirclesPairs, self._firstColor,
                          self._firstDrawStyle)
        self._drawCircles(self._secondCirclesPairs, self._secondColor)
        self._draw_coordinate_axes()
        self._painter.end()

    def _drawCircles(self, array, color, paintStyle=Qt.SolidLine):
        pen = QPen()

        for pair in array:
            pen.setStyle(paintStyle)
            for circle in pair:
                center = QPoint(*self._zoom_and_move_cords(*circle[0]))
                pen.setWidth(5)
                pen.setColor(color[1])
                self._painter.setPen(pen)
                self._painter.drawPoint(center)
                pen.setWidth(2)
                pen.setColor(color[0])
                self._painter.setPen(pen)
                self._painter.drawEllipse(center, circle[1] * self._kx, circle[1] * self._ky)

            pen.setWidth(1)
            pen.setColor(QColor(color[2]))
            pen.setStyle(Qt.SolidLine)
            self._painter.setPen(pen)

            if pair[0][0][0] + pair[0][1] == pair[1][0][0] - pair[1][1]:
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

    def _zoom_and_move_cords(self, x, y):
        x = self._kx * x + self._xm
        y = self.height() - (self._ky * y + self._ym)

        return [x, y]


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
        # self._firstCirclesPairs = [
        #         [[[1, 5], 2], [[4, 1], 1]],
        #         [[[1, 5], 2], [[5, -3], 2]],
        #         [[[5, -3], 2], [[9, 3], 2]],
        #         ]
        #
        # self._secondCirclesPairs = [
        #         [[[9, 5], 1], [[14, 6], 3]],
        #         ]

        # self._firstCirclesPairs = [
        #     [[[1, 5], 2], [[4, 1], 1]],
        #     [[[1, 5], 2], [[5, -3], 2]],
        # ]
        #
        # self._secondCirclesPairs = [
        #     [[[5, -3], 2], [[9, 3], 2]],
        #     [[[9, 5], 1], [[14, 6], 3]],
        # ]

        for i in range(len(self._firstCirclesPairs)):
            for j in range(2):
                self._firstCirclesPairs[i][j][0][0] += 0
                self._firstCirclesPairs[i][j][1] *= 1

        for i in range(len(self._secondCirclesPairs)):
            for j in range(2):
                self._secondCirclesPairs[i][j][0][0] -= 0
                self._secondCirclesPairs[i][j][1] *= 1

        self._get_zoom_coefficients()

        self._resultLabel = QLabel(self._resultInfo)
        self._paintField = PaintField(self, self._firstCirclesPairs,
                                      self._secondCirclesPairs)

#        self._paintField.setFixedSize(self.WINDOW_WIDTH, self.WINDOW_HEIGHT)
        # self._paintField.setFixedSize(self.width(), self.height())
        self._mainLayout = QVBoxLayout()
        self._mainLayout.addWidget(self._resultLabel) 
        self._mainLayout.addWidget(self._paintField)
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

        height = self.height() * self.PAINT_FIELD_HEIGHT_COEF

        real_width = abs(max_right - max_left)
        real_height = abs(max_top - max_bottom)
        
        self.ky = height / real_height
        self.kx = self.width() / real_width

        self.kx = min(self.kx, self.ky)
        self.ky = self.kx

        self.xm = -self.kx * max_left
        self.ym = -self.ky * max_bottom


    def initGUI(self):
        self.show()
