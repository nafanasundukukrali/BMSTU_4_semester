from PySide6.QtCore import QPoint
from PySide6.QtWidgets import QLabel, QVBoxLayout, QWidget
import itertools
import copy
from PySide6.QtGui import QPainter, QColor, QBrush

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
    def _comparatorSameCoords(coords1, coords2):
        return coords1[0] == coords2[0] and coords1[1] == coords2[1]
    @staticmethod
    def _comparatorSameCircles(circle1, circle2):
        return circle1[0] == circle2[0] and (circle1[1] == circle2[1] and 
                                             circle1[2] == circle2[2] or 
                                             circle1[1] == circle2[2] and
                                             circle1[2] == circle2[1])
    def _analysData(self): 
        def get_distance_by_coords(coords1, coords2):
            return ((coords1[0] - coords2[0])**2 +
                    (coords1[1] - coords2[1])**2)**0.5

        def get_compare_params(circle_data):
            radius = get_distance_by_coords(circle_data[0], circle_data[1])
            x_left = circle_data[i][0][0] - radius
            x_right = circle_data[i][0][0] + radius
            y = circle_data[i][0][1]
            
            return {'radius': radius, 
                    'x_left': x_left,
                    'x_right': x_right,
                    'y': y}

        all_circles = list(itertools.permutations(self.array, 3))
        self._removeDuplicates(all_circles, self._comparatorSameCircles)

        for i in range(len(all_circles)):
            circle1_data = get_compare_params(all_circles[i])

            for j in range(i + 1, len(all_circles)):
                circle2_data = get_compare_params(all_circles[j])
                centers_distance = get_distance_by_coords(all_circles[i][0],
                                                          all_circles[j][0])

                if ((centers_distance >= abs(circle1_data['radius'] + 
                                           circle2_data['radius'])) and 
                    (circle1_data['x_left'] == circle2_data['x_right'] or
                     circle1_data['x_right'] == circle2_data['x_left'])):
                        self.circles_paires.append([all_circles[i],
                                                    all_circles[j]])


class PaintField(QWidget):

    def __init__(self, firstCirclesPairs, secondCirclesPairs):
        super().__init__()

        self._firstColor = QColor(200, 0, 0)
        self._secondColor = QColor(255, 80, 0, 160)

        self._firstCirclesPairs = firstCirclesPairs
        self._secondCirclesPairs = secondCirclesPairs

       # self.slider = QSlider(self)
       # self.slider.move(360, 30)
       # self.slider.resize(30, 350)
       # self.slider.setInvertedAppearance(True)
       # self.slider.setValue(50)
       # self.slider.valueChanged.connect(self.update)

        # self.show()
    

    def paintEvent(self, event):

        self._painter = QPainter(self)

        self._drawCircles(self._firstCirclesPairs, self._firstColor)
        self._drawCircles(self._secondCirclesPairs, self._secondColor)


    def _drawCircles(self, array, color):
        self._painter.setBrush(color)

        for pair in array:
            for circle in pair:
                center = QPoint(circle[0][0], circle[0][1])
                self._painter.drawEllipse(center,
                                      circle[1], circle[1])

        
        
class ResultWindow(QWidget):

    def __init__(self, firstData, secondData):
        super().__init__()
        self._resultInfo = ""
        # self._firstCirclesPairs = Circles(firstData)
        # self._secondCirclesPairs = Circles(secondData)
        self._firstCirclesPairs = [
                [[[1, 5], 2], [[4, 1], 1]],
                [[[1, 5], 2], [[5, -3], 2]],
                [[[5, -3], 2], [[9, 3], 2]],
                ]

        self._secondCirclesPairs = [
                [[[10, 5], 1], [[14, 6], 3]],
                ]
        
        self._resultLabel = QLabel(self._resultInfo)
        self._paintField = PaintField(self._firstCirclesPairs,
                                      self._secondCirclesPairs)

        self._paintField.setMinimumSize(300, 400)

        self._mainLayout = QVBoxLayout()
        self._mainLayout.addWidget(self._resultLabel) 
        self._mainLayout.addWidget(self._paintField)

        self.initGUI()

    def initGUI(self):
        self.show()
