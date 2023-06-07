from PySide6.QtCore import QPoint
from config import MessageDisplay
from enum import Enum

class DrawMode(Enum):
    splitter = 1
    line = 2

# Отсекатель

class DrawingData:
    MAX_CUTS_COUNT=10
    EPSILON=1e-3

    def __init__(self, parent):
        self._splitter = None
        self._splitter_index = 0
        self._cuts = []
        self._last_point = None
        self._start_point = None
        self._parent = parent

    def add_point(self, dot: QPoint, type: DrawMode):
        if type == DrawMode.splitter:
            if self._last_point is None and not (self._start_point is None):
                if self._start_point == dot:
                    return MessageDisplay(self._parent, "Невозможно создать отсекатель, поскольку введённые координаты вершин совпадают.")

                self._last_point = dot
                self._splitter = [self._start_point, self._last_point]
                self._splitter_index = len(self._cuts)
            else:
                self._last_point = None
                self._start_point = dot
        else:
            if self._last_point is None and not(self._start_point is None):
                if len(self._cuts) == self.MAX_CUTS_COUNT:
                    return MessageDisplay(self._parent, f'Невозможно добавить отрезок, достигнуто максимальное количество: {self.MAX_CUTS_COUNT}')

                self._last_point = dot
                self._cuts.append([self._start_point, self._last_point])
            else:
                self._start_point = dot
                self._last_point = None

    def reset_actual_point_data(self):
        self._last_point = None
        self._start_point = None

    def reset_all_data(self):
        self._splitter = None
        self._splitter_index = 0
        self._cuts = []
        self._last_point = None
        self._start_point = None

    def get_data(self):
        buffer = [[DrawMode.line, value] for value in self._cuts[:self._splitter_index]]

        if not (self._splitter is None):
            buffer.append([DrawMode.splitter, self._splitter])

        buffer = buffer + [[DrawMode.line, value] for value in self._cuts[self._splitter_index: len(self._cuts)]]

        return buffer

    def get_splitted_data(self):
        if self._splitter is None:
            return MessageDisplay(self._parent, "Невозможно показать результат, поскольку не были введены данные отсекателя.")

        x_left = min(self._splitter[0].x(), self._splitter[1].x())
        x_right = max(self._splitter[0].x(), self._splitter[1].x())
        y_top = min(self._splitter[0].y(), self._splitter[1].y())
        y_bottom = max(self._splitter[0].y(), self._splitter[1].y())

        result = []

        for cut in self._cuts:
            def test(point: QPoint):
                value = 0

                if point.x() < x_left:
                    value += 1
                if point.x() > x_right:
                    value += 2
                if point.y() > y_bottom:
                    value += 4
                if point.y() < y_top:
                    value += 8

                return value

            test_first = test(cut[0])
            test_second = test(cut[1])

            if test_first == 0 and test_second == 0:
                result.append([DrawMode.line, cut])

            if (test_first == 2 and test_second == 6 or
                    test_first == 6 and test_second == 2 or
                    test_first == 8 and test_second == 2 or
                    test_first == 2 and test_second == 8):
                continue





