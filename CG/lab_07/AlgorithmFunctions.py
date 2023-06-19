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
        self._was_result = None

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
        self._was_result = None

    def get_was_status(self):
        return self._was_result

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
            def get_points_codes_sum(point: QPoint, x_left, x_right, y_top, y_bottom):
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

            first_sum = get_points_codes_sum(cut[0], x_left, x_right, y_top, y_bottom)
            second_sum = get_points_codes_sum(cut[1], x_left, x_right, y_top, y_bottom)

            P1_x, P1_y = float(cut[0].x()), float(cut[0].y())
            P2_x, P2_y = float(cut[1].x()), float(cut[1].y())

            if second_sum == 0:
                R_x = P2_x
                R_y = P2_y
            else:
                R_x = P1_x
                R_y = P1_y

            i = 0

            while i < 2 and not (first_sum == 0 and second_sum == 0) and first_sum & second_sum == 0:
                P_m_x = (P1_x + P2_x) / 2
                P_m_y = (P1_y + P2_y) / 2

                middle_sum = get_points_codes_sum(QPoint(P_m_x, P_m_y), x_left, x_right, y_top, y_bottom)

                if middle_sum & second_sum != 0 or middle_sum == 0 and second_sum == 0:
                    P2_x = P_m_x
                    P2_y = P_m_y
                else:
                    P1_x = P_m_x
                    P1_y = P_m_y

                if (P1_x - P2_x) ** 2 + (P1_y - P2_y) ** 2 < self.EPSILON ** 2:
                    if (get_points_codes_sum(QPoint(P1_x, P1_y), x_left, x_right, y_top, y_bottom) != 0 and
                            get_points_codes_sum(QPoint(P2_x, P2_y), x_left, x_right, y_top, y_bottom) == 0):
                        R_x, R_y, P2_x, P2_y, P1_x, P1_y = P2_x, P2_y, R_x, R_y, P2_x, P2_y
                    else:
                        P1_x, P1_y, P2_x, P2_y, R_x, R_y = P2_x, P2_y, R_x, R_y, P1_x, P1_y

                    i += 1

                first_sum = get_points_codes_sum(QPoint(P1_x, P1_y), x_left, x_right, y_top, y_bottom)
                second_sum = get_points_codes_sum(QPoint(P2_x, P2_y), x_left, x_right, y_top, y_bottom)

                if i == 1 and first_sum == 0 and second_sum == 0:
                    i += 1

            first_sum = get_points_codes_sum(QPoint(R_x, R_y), x_left, x_right, y_top, y_bottom)

            if first_sum & second_sum != 0:
                continue

            if first_sum == 0 and second_sum == 0:
                result.append([QPoint(R_x, R_y), QPoint(P2_x, P2_y)])

        self._was_result = result

        return result












