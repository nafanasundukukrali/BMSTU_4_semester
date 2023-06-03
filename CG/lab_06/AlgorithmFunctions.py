from PySide6.QtCore import QPoint

class Figure:
    def __init__(self, start_point: QPoint):
        self._start_point = start_point
        self._actual_point = start_point

    def add_point(self, dot: QPoint):
        self._actual_point = dot

    def get_start_point(self):
        return self._start_point

    def get_actual_point(self):
        return self._actual_point
