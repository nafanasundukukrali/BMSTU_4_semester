import numpy
from PySide6.QtCore import QPoint
from config import MessageDisplay
from enum import Enum
from math import fabs, copysign
from copy import deepcopy
import numpy as np

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

    def get_edges(self):
        buffer = deepcopy(self._edges)

        return buffer

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

    def __len__(self):
        return len(self._edges)


class DrawingData:
    def __init__(self, parent):
        self._splitter = None
        self._figure = None
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
            if self._figure is None:
                self._figure = Figure(dot, self._parent)
            else:
                if self._figure.get_actual_point() == self._figure.get_start_point() and len(self._figure) > 1:
                    self._figure = Figure(dot, self._parent)
                    self._cuts = list(filter(lambda x: x[0] != DrawMode.line, self._cuts))
                else:
                    self._cuts.append([DrawMode.line, [self._figure.get_actual_point(), dot]])
                    self._figure.add_point(dot)

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

    def close(self, type: DrawMode):
        if type == DrawMode.splitter and self._splitter is None:
            return MessageDisplay(self._parent, "Отсекатель отсуствует.")

        if type == DrawMode.line and self._figure is None:
            return MessageDisplay(self._parent, "Многоугольник отсуствует.")

        return self.add_point(self._splitter.get_start_point() if type == DrawMode.splitter else
                              self._figure.get_start_point(), type)

    def get_splitted_data(self):
        if self._splitter is None:
            return MessageDisplay(self._parent, "Отсекатель не существует.")

        if self._figure is None:
            return MessageDisplay(self._parent, "Многоугольник не существует.")

        if self._splitter.get_actual_point() != self._splitter.get_start_point():
            return MessageDisplay(self._parent, "Отсекатель не замкнут")

        if self._figure.get_actual_point() != self._figure.get_start_point():
            return MessageDisplay(self._parent, "Отсекатель не замкнут")

        check_result = self._splitter.check_figure_is_convex_polygon()

        if not check_result:
            return MessageDisplay(self._parent, "Отсекатель не выпуклый")

        if type(check_result) == MessageDisplay:
            return

        self._cuts = list(filter(lambda x: x[0] != DrawMode.result, self._cuts))

        figure = self._figure.get_edges()

        splitter = self._splitter.get_edges()

        vector_2 = Vector(splitter[0][0], splitter[0][1])
        vector_1 = Vector(splitter[1][0], splitter[1][1])

        if vector_2.get_vertex_mul(vector_1):
            for i in range(len(splitter)):
                splitter[i].reverse()

            splitter.reverse()

        vector_2 = Vector(figure[0][0], figure[0][1])
        vector_1 = Vector(figure[1][0], figure[1][1])

        if vector_2.get_vertex_mul(vector_1):
            for i in range(len(figure)):
                figure[i].reverse()

            figure.reverse()

            # for i in range(len(figure)):
            #     figure[i].reverse()
            #
            # figure.reverse()

        for i in range(len(splitter)):
            edge = Vector(splitter[i][0], splitter[i][1])
            last_point = None
            buffer_result = []

            for j in range(len(figure)):
                start_vector = Vector(splitter[i][0], figure[j][0])
                end_vector = Vector(splitter[i][0], figure[j][1])

                vector_mul_start = start_vector.get_vertex_mul(edge)
                vector_mul_end = end_vector.get_vertex_mul(edge)

                if vector_mul_end > 0 and vector_mul_start > 0:
                    if last_point is not None and last_point != figure[j][0]:
                        buffer_result.append([last_point, figure[j][0]])

                    buffer_result.append([figure[j][0], figure[j][1]])
                    last_point = figure[j][1]
                elif vector_mul_start * vector_mul_end < 0:
                    system = numpy.array([[figure[j][1].x() - figure[j][0].x(),
                                           -(splitter[i][1].x() - splitter[i][0].x())],
                                          [figure[j][1].y() - figure[j][0].y(),
                                           -(splitter[i][1].y() - splitter[i][0].y())]])
                    result = [splitter[i][0].x() - figure[j][0].x(),
                              splitter[i][0].y() - figure[j][0].y()]

                    t = np.linalg.solve(system, result)[0]
                    point = figure[j][0] + (figure[j][1] - figure[j][0]) * t

                    if last_point is not None:
                        buffer_result.append([last_point, point])

                    if vector_mul_start > 0:
                        buffer_result.append([figure[j][0], point])
                        last_point = point
                    else:
                        buffer_result.append([point, figure[j][1]])
                        last_point = figure[j][1]
                elif vector_mul_start == 0 and vector_mul_end > 0:
                    if last_point is not None and last_point != figure[j][0]:
                        buffer_result.append([last_point, figure[j][0]])

                    buffer_result.append([figure[j][0], figure[j][1]])
                    last_point = figure[j][1]
                elif vector_mul_start == 0 and vector_mul_start > 0:
                    if last_point is not None and last_point != figure[j][0]:
                        buffer_result.append([last_point, figure[j][1]])

                    buffer_result.append([figure[j][0], figure[j][1]])
                    last_point = figure[j][0]
                elif vector_mul_end == 0:
                    if last_point is not None and last_point != figure[j][1]:
                        buffer_result.append([last_point, figure[j][1]])

                    last_point = figure[j][1]
                elif vector_mul_start == 0:
                    if last_point is not None and last_point != figure[j][0]:
                        buffer_result.append([last_point, figure[j][0]])

                    last_point = figure[j][0]

            if len(buffer_result) > 2 and buffer_result[0][0] != buffer_result[-1][1]:
                buffer_result.append([buffer_result[0][0], buffer_result[-1][1]])

            figure = buffer_result

        for cut in figure:
            self._cuts.append([DrawMode.result, cut])

        return figure




















