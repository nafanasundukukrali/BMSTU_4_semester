from PySide6.QtCore import QPoint
from math import fabs


class Node:
    def __init__(self, n, x, dy, deltax):
        self._horizontal = False
        self._n = n
        self._x = x
        self._dy = dy

        if dy == 0:
            self._dx = 0
            self._horizontal = True
        else:
            self._dx = deltax / float(dy)

        self._end_n = self._n - self._dy
        self._next = None

    def is_horizontal(self):
        return self._horizontal

    def get_end_n(self):
        return self._end_n

    def is_active(self, line):
        return line <= self._n and line >= self._n - self._dy

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
        return (other is not None and (
            self._n == other.get_n() and
            self._dy == other.get_dy() and
            self._x == other.get_x() and
            self._dx == other.get_dx()))

    def __gt__(self, other):
        return (other != None and (self._n > other.get_n() or self._n == other.get_n() and self._dy < other.get_dy()))

    def __lt__(self, other):
        return (other != None and (self._n < other.get_n() or self._n == other.get_n() and self._dy > other.get_dy()))

    def __le__(self, other):
        return (other != None and self._n <= other.get_n())

    def __str__(self):
        return f'[ n = {self._n} x = {self._x} dx = {self._dx} dy = {self._dy}]'


class Edges:
    def __init__(self):
        self._edges_list = None
        self._count = 0

    def insert(self, n, x, dy, deltax):
        buffer = Node(n, x, dy, deltax)

        buffer_1 = self._edges_list
        buffer_2 = None

        while buffer_1 != None and buffer_1 > buffer:
            buffer_2 = buffer_1
            buffer_1 = buffer_1.get_next()

        if buffer_2 == None:
            buffer.set_next(self._edges_list)
            self._edges_list = buffer
            self._count += 1

        elif buffer_2 != buffer:
            buffer_2.set_next(buffer)
            buffer.set_next(buffer_1)
            self._count += 1

    def get_active_edges(self, active_line):

        buffer_1 = self._edges_list

        while buffer_1 != None and active_line > buffer_1.get_n():
            buffer_1 = buffer_1.get_next()

        start = buffer_1

        while buffer_1 != None and active_line <= buffer_1.get_n() and active_line >= buffer_1.get_end_n():
            buffer_1 = buffer_1.get_next()

        end = buffer_1

        return start, end

    @staticmethod
    def move_start(start: Node, actual_line):
        while start != None and actual_line < start.get_n() - start.get_dy():
            start = start.get_next()

        return start

    @staticmethod
    def move_end(end: Node, actual_line):
        while end != None and actual_line < end.get_n():
            end = end.get_next()

        return end

    def get_edges_list(self):
        return self._edges_list

    def __del__(self):
        while self._edges_list != None:
            buffer_1 = self._edges_list.get_next()
            del self._edges_list
            self._edges_list = buffer_1

    def __str__(self):
        str_out = ""

        buffer: Node = self._edges_list

        while buffer != None:
            str_out = f'{str_out} {buffer.__str__()}'
            buffer = buffer.get_next()

        return str_out

    def __len__(self):
        return self._count


class Figure:
    def __init__(self, edges: Edges, start_point: QPoint):
        self._edges = edges
        self._start_point = start_point
        self._actual_point = start_point

    def add_point(self, dot: QPoint):
        n = max(dot.y(), self._actual_point.y())
        dy = abs(dot.y() - self._actual_point.y())
        x = dot.x() if dot.y() > self._actual_point.y() else self._actual_point.x()
        deltax = dot.x() - self._actual_point.x() if dot.y() > self._actual_point.y() else self._actual_point.x() - dot.x()

        self._edges.insert(n, x, dy, deltax)

        self._actual_point = dot

    def get_start_point(self):
        return self._start_point

    def get_actual_point(self):
        return self._actual_point

# node_1 = Node(10, 13, 14)
# node_2 = Node(3, 14, 19)
#
# print(node_1 <= node_2)
#
# edges = Edges()
# edges.insert(10, 13, 14)
# edges.insert(3, 14, 19)
# edges.insert(50, 5, 6)
# edges.insert(1, 1, 1)
# print(edges)
# value = edges.get_active_edges(11)
# print(*value)
# del edges
