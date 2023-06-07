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

    @analyzer
    def draw_data(self, has_delay=False):
        pass
        # if self._actual_start is None:
        #     return MessageDisplay(self, "Не был введён начальный затравочный пиксель.")
        #
        # color = self._image.pixelColor(self._actual_start)
        #
        # if color == self._splitter_color:
        #     return MessageDisplay(self, "Выбран в качестве затравочного пикселя пиксель на границе..")
        #
        # stack = [deepcopy(self._actual_start)]
        #
        # while len(stack):
        #     actual_dot: QPoint = stack.pop()
        #     color = self._image.pixelColor(actual_dot)
        #     self._draw_point(actual_dot)
        #
        #     start_dot = deepcopy(actual_dot)
        #     actual_dot.setX(actual_dot.x() - 1)
        #     color = self._image.pixelColor(actual_dot)
        #
        #     while actual_dot.x() != 0 and color != self._splitter_color:
        #         self._draw_point(actual_dot)
        #         actual_dot.setX(actual_dot.x() - 1)
        #         color = self._image.pixelColor(actual_dot)
        #
        #     x_left = actual_dot.x() + 1
        #     actual_dot = start_dot
        #     actual_dot.setX(actual_dot.x() + 1)
        #
        #     color = self._image.pixelColor(actual_dot)
        #
        #     while actual_dot.x() < self._image.width() - 1 and color != self._splitter_color:
        #         self._draw_point(actual_dot)
        #         actual_dot.setX(actual_dot.x() + 1)
        #         color = self._image.pixelColor(actual_dot)
        #
        #     x_right = actual_dot.x() - 1
        #
        #     def add_to_stack_new_start_dot():
        #         while actual_dot.x() <= x_right:
        #             flag = False
        #             color = self._image.pixelColor(actual_dot)
        #
        #             while actual_dot.x() <= x_right and color != self._splitter_color and color != self._lines_color:
        #                 if flag == False:
        #                     flag = True
        #
        #                 actual_dot.setX(actual_dot.x() + 1)
        #                 color = self._image.pixelColor(actual_dot)
        #
        #             if flag == True:
        #                 color = self._image.pixelColor(actual_dot)
        #
        #                 if actual_dot.x() == x_right and color != self._splitter_color and color != self._lines_color:
        #                     stack.append(deepcopy(actual_dot))
        #                 else:
        #                     buffer = deepcopy(actual_dot)
        #                     buffer.setX(actual_dot.x() - 1)
        #                     stack.append(deepcopy(buffer))
        #
        #             x_in = actual_dot.x()
        #             color = self._image.pixelColor(actual_dot)
        #
        #             while color == self._splitter_color or self._splitter_color == self._lines_color and actual_dot.x() < x_right:
        #                 actual_dot.setX(actual_dot.x() + 1)
        #                 color = self._image.pixelColor(actual_dot)
        #
        #             if actual_dot.x() == x_in:
        #                 actual_dot.setX(actual_dot.x() + 1)
        #
        #     actual_dot.setX(x_left)
        #
        #     if actual_dot.y() - 1 >= 1:
        #         actual_dot.setY(actual_dot.y() - 1)
        #         add_to_stack_new_start_dot()
        #
        #     actual_dot.setX(x_left)
        #
        #     if actual_dot.y() + 2 < self._image.height():
        #         actual_dot.setY(actual_dot.y() + 2)
        #         add_to_stack_new_start_dot()
        #
        #     if has_delay:
        #         if has_delay:
        #             loop = QEventLoop()
        #             QTimer.singleShot(50, loop.quit)
        #             loop.exec()


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

    def add_point(self, dot: QPoint):
        if not (self._actual_figure.add_point(dot, self._actual_draw_point_status) is None):
            return

        self._draw_figure_data()

        self.update()

    def _draw_figure_data(self):
        self._image.fill(Qt.transparent)
        painter = QPainter(self._image)
        pen = QPen()
        pen.setColor(self._lines_color)
        painter.setPen(pen)

        data: list[[DrawMode, [QPoint, QPoint]]] = self._actual_figure.get_data()
        i = 0

        while i < len(data) and data[i][0] == DrawMode.line:
            painter.drawLine(data[i][1][0], data[i][1][1])
            i += 1

        if i < len(data):
            pen.setColor(self._splitter_color)
            painter.setPen(pen)

            w = data[i][1][1].x() - data[i][1][0].x()
            h = data[i][1][1].y() - data[i][1][0].y()
            painter.drawRect(data[i][1][0].x(), data[i][1][0].y(), w, h)

            i += 1

        pen.setColor(self._lines_color)
        painter.setPen(pen)

        while i < len(data):
            painter.drawLine(data[i][1][0], data[i][1][1])
            i += 1

        painter.end()

    def draw_splitter(self, firstPoint: QPoint, secondPoint: QPoint):
        self._actual_figure.reset_actual_point_data()
        self._actual_figure.add_point(firstPoint, DrawMode.splitter)
        self._actual_figure.add_point(secondPoint, DrawMode.splitter)

        self._draw_figure_data()

    def mousePressEvent(self, ev):
        if self._check_event(ev) == 1:
            ev.accept()
            dot = QPoint(ev.x(), ev.y())
            self.add_point(dot)

    def clean(self):
        self._image.fill(Qt.transparent)
        self._actual_figure.reset_all_data()
        self.update()
