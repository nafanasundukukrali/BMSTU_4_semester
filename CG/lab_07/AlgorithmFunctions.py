from PySide6.QtCore import QPoint
from config import MessageDisplay
from enum import Enum
from math import fabs

class DrawMode(Enum):
    splitter = 1
    line = 2

# Отсекатель

class DrawingData:
    MAX_CUTS_COUNT=10
    EPSILON=1e-1

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

        if len(self._cuts) == 0:
            MessageDisplay(self._parent, "Невозможно показать результат, поскольку не были введены данные ни по одному отрезку.")

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

            def get_ends_of_cut_result(p1: QPoint, p2: QPoint):
                test_first = test(p1)
                test_second = test(p2)

                if test_first & test_second != 0:
                    return 0

                if (test_first == 2 and test_second == 6 or
                        test_first == 6 and test_second == 2 or
                        test_first == 8 and test_second == 2 or
                        test_first == 2 and test_second == 8):
                    return 0

                if test_first == 0 and test_second == 0:
                    return 1

                return 3

            cuts_reuslt = get_ends_of_cut_result(cut[0], cut[1])

            if cuts_reuslt == 1:
                result.append([cut[0], cut[1]])
                continue

            if cuts_reuslt == 0:
                continue

            P1_x = cut[0].x()
            P1_y = cut[0].y()
            P2_x = cut[1].x()
            P2_y = cut[1].y()

            while fabs(P1_x - P2_x) > self.EPSILON or fabs(P1_y - P2_y) > self.EPSILON:
                    Pm_x = (P1_x + P2_x) / 2
                    Pm_y = (P1_y + P2_y) / 2

                    if get_ends_of_cut_result(QPoint(P1_x, P1_y), QPoint(Pm_x, Pm_y)) == 0:
                        P1_x = Pm_x
                        P1_y = Pm_y
                    else:
                        P2_x = Pm_x
                        P2_y = Pm_y

            if test(QPoint(P1_x, P1_y)) != 0 and test(QPoint(P2_x, P2_y)) == 0:
                R1 = QPoint(P2_x, P2_y)
            else:
                R1 = QPoint(P1_x, P1_y)

            P1_x = cut[0].x()
            P1_y = cut[0].y()
            P2_x = cut[1].x()
            P2_y = cut[1].y()

            while fabs(P1_x - P2_x) > self.EPSILON or fabs(P1_y - P2_y) > self.EPSILON:
                Pm_x = (P1_x + P2_x) / 2
                Pm_y = (P1_y + P2_y) / 2

                if get_ends_of_cut_result(QPoint(P2_x, P2_y), QPoint(Pm_x, Pm_y)) == 0:
                    P2_x = Pm_x
                    P2_y = Pm_y
                else:
                    P1_x = Pm_x
                    P1_y = Pm_y

            if test(QPoint(P2_x, P2_y)) != 0 and test(QPoint(P1_x, P1_y)) == 0:
                R2 = QPoint(P1_x, P1_y)
            else:
                R2 = QPoint(P2_x, P2_y)

            if get_ends_of_cut_result(R1, R2) == 1:
                result.append([R1, R2])

        return result












