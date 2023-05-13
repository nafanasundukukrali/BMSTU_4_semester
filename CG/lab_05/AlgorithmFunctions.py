from dataclasses import dataclass

from Analyzer import analyzer
from PySide6.QtCore import QPoint
from PySide6.QtWidgets import QGraphicsScene
from math import floor, pi, cos, sin


class Node:
    def __init__(self, n, x, dy):
        self._n = n
        self._x = x
        self._dy = dy
        self._dx = x / dy
        self._next = None

    def get_n(self):
        return self._n

    def get_x(self):
        return self._x

    def get_dy(self):
        return self._dy

    def get_dx(self):
        return self._dx

    def get_next(self):
        return self._next

    def set_next(self, next_node):
        self._next = next_node

    def __eq__(self, other):
        return (self._next == other.get_next() and
            self._n == other.get_n() and
            self._dy == other.get_dy() and
            self._x == other.get_x)

class Edges:
    def  __init__(self):
        self._edges_list = None

    def insert(self, n, x, dy):
        buffer = Node(n, x, dy)

        buffer_1 = self._edges_list
        buffer_2 = None

        while buffer_1 != None and buffer_1.get_n() >= buffer.get_n():
            buffer_2 = buffer_1
            buffer_1 = buffer_1.get_next()

        while buffer_1 != None and buffer_1.get_x() >= buffer.get_x():
            buffer_2 = buffer_1
            buffer_1 = buffer_1.get_next()

        if buffer_2 == None:
            self._edges_list = buffer
        elif buffer_2 != buffer:
            buffer_2.set_next(buffer)
            buffer.set_next(buffer_1)

    def get_active_edges(self, active_line):
        active_list = None
        buffer_1 = self._edges_list

        active_list = buffer_1

        while buffer_1 != None and active_line >= buffer_1.get_n():
            active_list.append(buffer_1)
            buffer_1 = buffer_1.get_next()

        return active_list



def get_symmetrical_pixes(array, x, y, x0, y0, intensive=255, is_circle=False):
    def scale_point(x1, y1, xm, ym, kx, ky):
        x1 = kx * x1 + (1 - kx) * xm
        y1 = ky * y1 + (1 - ky) * ym

        return QPoint(x1, y1)

    array.append([QPoint(x, y), intensive])
    array.append([scale_point(x, y, x0, y0, 1, -1), intensive])
    array.append([scale_point(x, y, x0, y0, -1, 1), intensive])
    array.append([scale_point(x, y, x0, y0, -1, -1), intensive])

    if is_circle:
        array.append([QPoint(y - y0 + x0,  x - x0 + y0), intensive])
        array.append([QPoint(-y + y0 + x0,  x - x0 + y0), intensive])
        array.append([QPoint(y - y0 + x0, -x + x0 + y0), intensive])
        array.append([QPoint(-y + y0 + x0, -x + x0 + y0), intensive])


def get_sign(x):
    if x > 0:
        return 1
    elif x < 0:
        return -1
    else:
        return 0


class AlgorithmFunctions:

    def __init__(self):
        return

    def get_algorithms_list(self):
        return {"Каноническое уравнение": [self.paint_circle_by_cartesian_form, self.paint_ellipse_by_cartesian_form],
                "Параметрическое уравнение": [self.paint_circle_by_params_form, self.paint_ellipse_by_params_form],
                "Метод средней точки": [self.paint_circle_by_middle_square, self.paint_ellipse_by_middle_square],
                "Алгоритм Брезенхема": [self.paint_circle_by_brethenhem, self.paint_ellipse_by_brethenhem],
                "Метод библиотеки PyQt": [self.paint_circle_by_library_function,
                                          self.paint_ellipse_by_library_function],
                }

    @staticmethod
    @analyzer
    def paint_circle_by_cartesian_form(start_cords: QPoint, r):
        result = []
        x0 = start_cords.x()
        y0 = start_cords.y()

        for x in range(x0, round(x0 + r / (2 ** 0.5)) + 1):
            y = round((r**2 - (x - x0)**2) ** 0.5) + y0
            get_symmetrical_pixes(result, x, y, x0, y0, is_circle=True)

        return result

    @staticmethod
    @analyzer
    def paint_ellipse_by_cartesian_form(start_cords: QPoint, a, b):
        result = []
        x0 = start_cords.x()
        y0 = start_cords.y()

        sqr_ra = a * a
        sqr_rb = b * b

        border_x = round(x0 + a / ((1 + sqr_rb / sqr_ra) ** 0.5))
        border_y = round(y0 + b / ((1 + sqr_ra / sqr_rb) ** 0.5))

        for x in range(round(x0), border_x + 1):
            y = round((sqr_ra * sqr_rb - (x - x0) ** 2 * sqr_rb) ** 0.5 / a) + y0
            get_symmetrical_pixes(result, x, y, x0, y0)

        for y in range(border_y, round(y0) - 1, -1):
            x = round((sqr_ra * sqr_rb - (y - y0) ** 2 * sqr_ra) ** 0.5 / b) + x0
            get_symmetrical_pixes(result, x, y, x0, y0)

        return result

    @staticmethod
    @analyzer
    def paint_circle_by_params_form(start_cords: QPoint, r):
        result = []
        x0 = start_cords.x()
        y0 = start_cords.y()

        t0 = 1 / r
        t = pi / 4

        while t <= pi / 2:
            x = x0 + round(r * cos(t))
            y = y0 + round(r * sin(t))
            get_symmetrical_pixes(result, x, y, x0, y0, is_circle=True)

            t += t0

        return result

    @staticmethod
    @analyzer
    def paint_ellipse_by_params_form(start_cords: QPoint, a, b):
        result = []
        x0 = start_cords.x()
        y0 = start_cords.y()

        if a > b:
            t0 = 1 / a
        else:
            t0 = 1 / b

        t = 0

        while t <= pi / 2:
            x = x0 + round(a * cos(t))
            y = y0 + round(b * sin(t))
            get_symmetrical_pixes(result, x, y, x0, y0)

            t += t0

        return result

    @staticmethod
    @analyzer
    def paint_circle_by_middle_square(start_cords: QPoint, r):
        result = []
        x0 = round(start_cords.x())
        y0 = round(start_cords.y())
        x = round(r)
        y = 0
        step = 1 - r

        get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0, is_circle=True)

        while x >= y:
            if step < 0:
                y += 1
                step += 2 * y + 1
            else:
                y += 1
                x -= 1
                step += 2 * y + 1 - 2 * x

            get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0, is_circle=True)

        return result

    @staticmethod
    @analyzer
    def paint_ellipse_by_middle_square(start_cords: QPoint, a, b):
        result = []
        x0 = round(start_cords.x())
        y0 = round(start_cords.y())
        x = 0
        y = round(b)
        d = b ** 2 - a ** 2 * (b - 1/4)

        get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0)

        while 2 * (b ** 2) * x < 2 * (a ** 2) * y:
            if d < 0:
                x += 1
                d += b ** 2 * 2 * x + b ** 2
            else:
                x += 1
                y -= 1
                d += b ** 2 * 2 * x - a ** 2 * 2 * y + b ** 2

            get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0)

        x = round(a)
        y = 0

        d = a ** 2 - b ** 2 * (a - 1/4)

        get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0)

        while 2 * (b ** 2) * x > 2 * (a ** 2) * y:
            if d < 0:
                y += 1
                d += a ** 2 * 2 * y + a ** 2
            else:
                y += 1
                x -= 1
                d += a ** 2 * 2 * y - b ** 2 * 2 * x + a ** 2

            get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0)

        return result

    @staticmethod
    @analyzer
    def paint_circle_by_brethenhem(start_cords: QPoint, r):
        result = []
        x0 = round(start_cords.x())
        y0 = round(start_cords.y())
        x = 0
        y = round(r)
        d = 2 * (1 - r)

        get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0, is_circle=True)

        while x <= y:
            d1 = 2 * (d + y) - 1
            x += 1

            if d1 <= 0:
                d += 2 * x + 1
            else:
                y -= 1
                d += 2 * (x - y + 1)

            get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0, is_circle=True)

        return result

    @staticmethod
    @analyzer
    def paint_ellipse_by_brethenhem(start_cords: QPoint, a, b):
        result = []
        x0 = round(start_cords.x())
        y0 = round(start_cords.y())
        x = 0
        y = round(b)
        sqr_ra = a * a
        sqr_rb = b * b
        d = sqr_rb - sqr_ra * (2 * b + 1)

        get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0)

        while y >= 0:

            if d < 0:
                d1 = 2 * d + sqr_ra * (2 * y + 2)

                x += 1
                if d1 < 0:
                    d += sqr_rb * (2 * x + 1)
                else:
                    y -= 1
                    d += sqr_rb * (2 * x + 1) + sqr_ra * (1 - 2 * y)
            elif d > 0:
                d2 = 2 * d + sqr_rb * (2 - 2 * x)

                y -= 1
                if d2 > 0:
                    d += sqr_ra * (1 - 2 * y)
                else:
                    x += 1
                    d += sqr_rb * (2 * x + 1) + sqr_ra * (1 - 2 * y)
            else:
                y -= 1
                x += 1
                d += sqr_rb * (2 * x + 1) + sqr_ra * (1 - 2 * y)

            get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0)

        return result
    #
    # @staticmethod
    # @analyzer
    # def paint_ellipse_by_brethenhem(start_cords: QPoint, a, b):
    #     result = []
    #     x0 = round(start_cords.x())
    #     y0 = round(start_cords.y())
    #     x = 0
    #     y = round(b)
    #     sqr_ra = a * a
    #     sqr_rb = b * b
    #     d = 4 * sqr_rb * ((x + 1) * (x + 1)) + sqr_ra * ((2 * y - 1) * (2 * y - 1)) - 4 * sqr_rb * sqr_ra
    #
    #     while sqr_ra * (2 * y - 1) >= 2 * sqr_rb * (x + 1):
    #         get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0)
    #          x += 1
    #         if d >= 0:
    #             d += 4 * sqr_rb * (2 * x + 3) - 8 * sqr_ra * (y - 1)
    #             y -= 1
    #         else:
    #             d += 4 * sqr_rb * (2 * x + 3)
    #
    #     # d = sqr_rb * ((2 * x + 1) ** 2) + 4 * sqr_ra * ((y - 1) ** 2) - 4 * sqr_rb * sqr_ra
    #
    #     while (y >= 0):
    #         y -= 1
    #
    #         if d < 0:
    #             d += 4 * sqr_ra * (2 * y + 3)
    #         else:
    #             d += 4 * sqr_ra * (2 * y + 3) - 8 * sqr_rb * (1 + x)
    #             x += 1
    #
    #         get_symmetrical_pixes(result, x0 + x, y0 + y, x0, y0)
    #
    #     return result

    @staticmethod
    @analyzer
    def paint_circle_by_library_function(center: QPoint, r):
        buffer = QGraphicsScene()
        buffer.addEllipse(*(center.toTuple()), r * 2, r * 2)
        del buffer

        return [[*(center.toTuple()), r * 2, r * 2]]

    @staticmethod
    @analyzer
    def paint_ellipse_by_library_function(center: QPoint, a, b):
        buffer = QGraphicsScene()
        buffer.addEllipse(*(center.toTuple()), a * 2, b * 2)
        del buffer

        return [[center.x() - a, center.y() - b, a * 2, b * 2]]
