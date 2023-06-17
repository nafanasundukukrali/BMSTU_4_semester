from PySide6.QtWidgets import QFrame
from PySide6.QtGui import QFont, QPainter, QPen, QColor, QPixmap, QImage
from PySide6.QtCore import QPoint, Qt, QTimer, QThread, QEventLoop
from AlgorithmFunctions import DrawingData, DrawMode
from Analyzer import analyzer
import time
from config import MessageDisplay, BASE_COLORS
from copy import deepcopy


class PaintField(QFrame):
    def __init__(self, params):
        super().__init__()
        self._labelFont = QFont("Times", 15, QFont.Bold)
        self.setFont(QFont("Times", 15, QFont.Bold))
        self.setFixedSize(*params)
        self._background = QPixmap(self.size())
        pixmap = QPixmap(self.size())
        self._image = pixmap.toImage()

        self._splitter_color = BASE_COLORS.splitter_color
        self._lines_color = BASE_COLORS.line_color
        self._result_color = BASE_COLORS.result_color
        self._background_color = BASE_COLORS.background_color
        self._background.fill(self._background_color)

        self._image.fill(Qt.transparent)

        self._cut_data = []
        self._actual_figure = DrawingData(self)
        self._actual_draw_point_status = DrawMode.splitter

    def paintEvent(self, event):
        super().paintEvent(event)
        painter = QPainter(self)
        painter.drawPixmap(QPoint(), self._background)
        painter.drawImage(QPoint(), self._image)

    def change_splitter_color(self, color: QColor):
        self._splitter_color = color
        self._draw_figure_data()
        self.update()

    def change_lines_color(self, color: QColor):
        self._lines_color = color
        self._draw_figure_data()
        self.update()

    def change_result_color(self, color: QColor):
        self._result_color = color

    def change_background_color(self, color: QColor):
        self._background_color = color
        self._background.fill(self._background_color)
        self.update()

    def draw_data(self):
        self._draw_figure_data()

        result = self._actual_figure.get_splitted_data()

        if type(result) == MessageDisplay:
            return

        painter = QPainter(self._image)
        pen = QPen()
        pen.setWidth(2)
        pen.setColor(self._result_color)
        painter.setPen(pen)

        for cut in result:
            painter.drawLine(cut[0], cut[1])

        painter.end()
        self.update()

    def _draw_point(self, dot: QPoint):
        self._image.setPixelColor(dot, self._lines_color)

        self.update()

    def _check_event(self, ev):
        if ev.button() != Qt.LeftButton:
            return 0
        if self.rect().contains(ev.x(), ev.y()):
            return 1
        return 0

    def change_point_select_status(self):
        if self._actual_draw_point_status == DrawMode.line:
            self._actual_draw_point_status = DrawMode.splitter
        else:
            self._actual_draw_point_status = DrawMode.line

        self._actual_figure.reset_actual_point_data()

    def add_point(self, dot: QPoint = None):
        if dot is None:
            self._actual_figure.close()
        else:
            self._actual_figure.add_point(dot, self._actual_draw_point_status)

        self._draw_figure_data()
        self.update()

    def close_figure(self):
        self.add_point()

    def _draw_figure_data(self):
        self._image.fill(Qt.transparent)
        painter = QPainter(self._image)
        pen = QPen()
        pen.setColor(self._lines_color)
        painter.setPen(pen)

        data: list[[DrawMode, [QPoint, QPoint]]] = self._actual_figure.get_data()
        i = 0

        while i < len(data):
            if data[i][0] == DrawMode.line and pen.color() != self._lines_color:
                pen.setColor(self._lines_color)
                painter.setPen(pen)

            if data[i][0] == DrawMode.splitter and pen.color() != self._splitter_color:
                pen.setColor(self._splitter_color)
                painter.setPen(pen)

            if data[i][0] == DrawMode.result and pen.color() != self._result_color:
                pen.setColor(self._result_color)
                pen.setWidth(2)
                painter.setPen(pen)

            painter.drawLine(data[i][1][0], data[i][1][1])
            pen.setWidth(3)
            painter.setPen(pen)
            painter.drawPoint(data[i][1][0])
            painter.drawPoint(data[i][1][1])
            pen.setWidth(1)
            painter.setPen(pen)

            i += 1

        painter.end()

    def mousePressEvent(self, ev):
        if self._check_event(ev) == 1:
            ev.accept()
            dot = QPoint(ev.x(), ev.y())
            self.add_point(dot)

    def clean(self):
        self._image.fill(Qt.transparent)
        self._actual_figure.reset_all_data()
        self.update()
