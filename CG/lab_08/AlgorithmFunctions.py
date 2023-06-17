from PySide6.QtCore import QPoint
from config import MessageDisplay
from enum import Enum
from math import fabs, copysign

class DrawMode(Enum):
    splitter = 1
    line = 2
    result = 3

class Vector:
    def __init__(self, start, end, vector_coords = True):
        if vector_coords:
            self._x = end.x() - start.x()
            self._y = end.y() - start.y()
        else:
            self._x = start
            self._y = end

    def get_x(self):
        return self._x

    def get_y(self):
        return self._y

    def set_x(self, x: float):
        self._x = x

    def set_y(self, y: float):
        self._y = y

    def get_vertex_mul(self, base) -> float:
        return base.get_x() * self._y - base.get_y() * self._x

    def get_scal_mul(self, vector):
        return vector.get_x() * self._x + vector.get_y() * self._y

    def get_normal(self, test):
        if self._x != 0:
            Nvn = Vector(-self._y / self._x, 1, False)
        else:
            Nvn = Vector(1, -self._x / self._y, False)

        if Nvn.get_scal_mul(test) < 0:
            Nvn.set_x(Nvn.get_x() * (-1))
            Nvn.set_y(Nvn.get_y() * (-1))

        return Nvn

# Отсекатель
class Figure:
    def __init__(self, start_point: QPoint, parent):
        self._vectors = []
        self._edges = []
        self._start_point = start_point
        self._actual_point = start_point
        self._parent = parent

    def add_point(self, dot: QPoint):
        self._edges.append([self._actual_point, dot])
        vector = Vector(self._actual_point, dot)
        self._vectors.append(vector)
        self._actual_point = dot

    def get_start_point(self):
        return self._start_point

    def get_actual_point(self):
        return self._actual_point

    def check_figure_is_finished(self):
        return self._start_point == self._actual_point

    def check_figure_is_convex_polygon(self):
        if len(self._edges) < 3:
            return MessageDisplay(self._parent, "Ошибка: меньше 3-х вершин, не является многоугольником.")

        sign = copysign(1, self._vectors[0].get_vertex_mul(self._vectors[-1]))

        sign_1 = sign

        i = 1

        while sign_1 == sign and i < len(self._edges):
            sign_1 = copysign(1, self._vectors[i].get_vertex_mul(self._vectors[i - 1]))
            i += 1

        return sign == sign_1

    def split_cut(self, P1: QPoint, P2: QPoint):
        tn = 0
        tk = 1

        D = Vector(P1, P2)

        added = []

        for i in range(len(self._vectors)):
            Nvn = self._vectors[i].get_normal(self._vectors[(i + 1) % len(self._vectors)])

            fi = self._edges[i][0]

            Wi = Vector(fi, P1)

            Dsk = D.get_scal_mul(Nvn)
            Wsk = Wi.get_scal_mul(Nvn)

            if Dsk == 0 and Wsk < 0:
                return
            elif Dsk != 0:
                t = - Wsk / Dsk

                if Dsk > 0:
                    if t > 1:
                        return

                    tn = max(tn, t)
                elif Dsk < 0:
                    if t < 0:
                        return

                    tk = min(tk, t)

        if tn <= tk:
            return [QPoint(P1.x() + (P2.x() - P1.x()) * tn,
                           P1.y() + (P2.y() - P1.y()) * tn),
                    QPoint(P1.x() + (P2.x() - P1.x()) * tk,
                           P1.y() + (P2.y() - P1.y()) * tk)]

    def __len__(self):
        return len(self._edges)


class DrawingData:
    def __init__(self, parent):
        self._splitter = None
        self._splitter_index = 0
        self._cuts = []
        self._last_result = None
        self._last_point = None
        self._start_point = None
        self._parent = parent

    def add_point(self, dot: QPoint, type: DrawMode):
        if type == DrawMode.splitter:
            if self._splitter is None:
                self._splitter = Figure(dot, self._parent)
            else:
                if self._splitter.get_actual_point() == self._splitter.get_start_point() and len(self._splitter) > 1:
                    self._splitter = Figure(dot, self._parent)
                    self._cuts = list(filter(lambda x: x[0] != DrawMode.splitter, self._cuts))
                else:
                    self._cuts.append([DrawMode.splitter, [self._splitter.get_actual_point(), dot]])
                    self._splitter.add_point(dot)
        else:
            if self._last_point is None and not(self._start_point is None):
                self._last_point = dot
                self._cuts.append([DrawMode.line, [self._start_point, self._last_point]])
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
        self._last_result = None

    def get_data(self):
        return self._cuts

    def close(self):
        if self._splitter is None:
            return MessageDisplay(self._parent, "Многоугольник пока не существует")

        return self.add_point(self._splitter.get_start_point(), DrawMode.splitter)

    def get_splitted_data(self):
        self._cuts = list(filter(lambda x: x[0] != DrawMode.result, self._cuts))
        cuts = list(filter(lambda x: x[0] == DrawMode.line, self._cuts))

        if self._splitter is None:
            return MessageDisplay(self._parent, "Многоугольник не существует")

        if self._splitter.get_actual_point() != self._splitter.get_start_point():
            return MessageDisplay(self._parent, "Многоугольник не замкнут")

        check_result = self._splitter.check_figure_is_convex_polygon()

        if not check_result:
            return MessageDisplay(self._parent, "Многоугольник не выпуклый")

        if type(check_result) == MessageDisplay:
            return

        result = []

        for cut in cuts:
            buffer_result = self._splitter.split_cut(cut[1][0], cut[1][1])

            if buffer_result is not None:
                self._cuts.append([DrawMode.result, buffer_result])
                result.append(buffer_result)

        return result




















