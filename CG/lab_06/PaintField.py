from PySide6.QtWidgets import QFrame
from PySide6.QtGui import QFont, QPainter, QPen, QColor, QPixmap
from PySide6.QtCore import QPoint, Qt, QTimer, QThread, QEventLoop
from AlgorithmFunctions import Edges, Figure
from Analyzer import analyzer
import time
from config import MessageDisplay


class PaintField(QFrame):
    def __init__(self, params):
        super().__init__()
        self._labelFont = QFont("Times", 15, QFont.Bold)
        self.setFont(QFont("Times", 15, QFont.Bold))
        self.setFixedSize(*params)
        self._background = QPixmap(self.size())
        self._image = QPixmap(self.size())
        self._pen_color = QColor(0, 0, 0)
        self._fill_color = QColor(0, 0, 0)
        self._background_color = QColor(255, 255, 255)
        self._background.fill(self._background_color)
        self._image.fill(Qt.transparent)
        self._edges = Edges()
        self._actual_figure = None

    def paintEvent(self, event):
        super().paintEvent(event)
        painter = QPainter(self)
        painter.drawPixmap(QPoint(), self._background)
        painter.drawPixmap(QPoint(), self._image)

    def close_figure(self):
        if self._actual_figure == None:
            return MessageDisplay(self, "Работа с многоульником не была начата.")

        self.add_point(self._actual_figure.get_start_point())

    def change_pen_color(self, color: QColor):
        self._pen_color = color

    def change_fill_color(self, color: QColor):
        self._fill_color = color

    def change_background_color(self, color: QColor):
        self._background_color = color
        self._background.fill(self._background_color)
        self.update()

    @analyzer
    def draw_data(self, has_delay=False):
        if self._actual_figure != None:
            return MessageDisplay(self, "Присутствует незамкнутый многоугольник.")

        if self._edges.get_edges_list() is None:
            return MessageDisplay(self, "Список рёбер пуст.")

        start, end = self._edges.get_active_edges(self._edges.get_edges_list().get_n())

        y_groups = []

        CAP = []

        buffer_start = start

        while buffer_start != end:
            CAP.append(buffer_start.copy())
            buffer_start = buffer_start.get_next()

        actual_line = start.get_n()
        real_start = start.get_n()

        while start != None:
            start = Edges.move_start(start, actual_line)

            while end != None and actual_line <= end.get_n():
                CAP.append(end.copy())
                end = end.get_next()

            y_groups.append([])
            delete_list = []
            CAP.sort(key=lambda value: value.get_x())

            for k in range(len(CAP)):
                i = 0

                while i < len(y_groups[-1]) and round(CAP[k].get_x()) != y_groups[-1][i]:
                    i += 1

                if i != len(y_groups[-1]) and y_groups[-1][i] == round(CAP[k].get_x()):
                    if (actual_line == CAP[k].get_n() and CAP[i].get_dy() < 0
                            or CAP[k].get_dy() == 0 and actual_line == CAP[i].get_n()):
                        delete_list.append(i)

                y_groups[-1].append(round(CAP[k].get_x()))

                CAP[k].minusY()
                CAP[k].minusX()

            for i in delete_list:
                y_groups[-1].pop(i)

            i = len(CAP) - 1

            while i > -1:
                if CAP[i].get_dy() < 1:
                    CAP.pop(i)

                i -= 1

            y_groups[-1].sort()

            actual_line -= 1

        for i in range(0, len(y_groups)):
            for j in range(0, len(y_groups[i]) - len(y_groups[i]) % 2, 2):
                self._draw_line(y_groups[i][j], y_groups[i][j + 1], real_start)

            if has_delay:
                loop = QEventLoop()
                QTimer.singleShot(50, loop.quit)
                loop.exec()

            real_start -= 1

    def _draw_line(self, start_x, end_x, actual_line):
        painter = QPainter(self._image)

        pen = QPen()
        pen.setColor(self._fill_color)
        painter.setPen(pen)

        while start_x < end_x:
            painter.drawPoint(start_x, actual_line)
            start_x += 1

        painter.end()

        self.update()

    def _check_event(self, ev):
        if ev.button() != Qt.LeftButton:
            return 0
        if self.rect().contains(ev.x(), ev.y()):
            return 1
        return 0

    def add_point(self, dot: QPoint):
        painter = QPainter(self._image)

        pen = QPen()
        pen.setColor(self._pen_color)
        painter.setPen(pen)

        if self._actual_figure is None:
            self._actual_figure = Figure(self._edges, dot)
        else:
            painter.drawLine(self._actual_figure.get_actual_point(), dot)
            self._actual_figure.add_point(dot)

            if self._actual_figure.get_start_point() == dot:
                del self._actual_figure
                self._actual_figure = None

        pen.setWidth(3)
        painter.setPen(pen)
        painter.drawPoint(dot)

        painter.end()

        self.update()

    def mousePressEvent(self, ev):
        if self._check_event(ev) == 1:
            ev.accept()
            dot = QPoint(ev.x(), ev.y())
            self.add_point(dot)

    def clean(self):
        self._image.fill(Qt.transparent)
        self._edges = Edges()
        self._actual_figure = None
        self.update()
