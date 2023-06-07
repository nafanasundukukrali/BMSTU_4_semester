from PySide6.QtWidgets import QFrame
from PySide6.QtGui import QFont, QPainter, QPen, QColor, QPixmap, QImage
from PySide6.QtCore import QPoint, Qt, QTimer, QThread, QEventLoop
from AlgorithmFunctions import Figure
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
        self._pen_color = BASE_COLORS.edges_color
        self._fill_color = BASE_COLORS.fill_color
        self._background_color = BASE_COLORS.background_color
        self._background.fill(self._background_color)
        self._image.fill(Qt.transparent)
        self._actual_figure = None
        self._actual_draw_point_status = False
        self._actual_start = None

    def paintEvent(self, event):
        super().paintEvent(event)
        painter = QPainter(self)
        painter.drawPixmap(QPoint(), self._background)
        painter.drawImage(QPoint(), self._image)

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
        if self._actual_start is None:
            return MessageDisplay(self, "Не был введён начальный затравочный пиксель.")

        color = self._image.pixelColor(self._actual_start)

        if color == self._pen_color:
            return MessageDisplay(self, "Выбран в качестве затравочного пикселя пиксель на границе зполняемой области.")

        stack = [deepcopy(self._actual_start)]

        while len(stack):
            actual_dot: QPoint = stack.pop()
            color = self._image.pixelColor(actual_dot)
            self._draw_point(actual_dot)

            start_dot = deepcopy(actual_dot)
            actual_dot.setX(actual_dot.x() - 1)
            color = self._image.pixelColor(actual_dot)

            while actual_dot.x() != 0 and color != self._pen_color:
                self._draw_point(actual_dot)
                actual_dot.setX(actual_dot.x() - 1)
                color = self._image.pixelColor(actual_dot)

            x_left = actual_dot.x() + 1
            actual_dot = start_dot
            actual_dot.setX(actual_dot.x() + 1)

            color = self._image.pixelColor(actual_dot)

            while actual_dot.x() < self._image.width() - 1 and color != self._pen_color:
                self._draw_point(actual_dot)
                actual_dot.setX(actual_dot.x() + 1)
                color = self._image.pixelColor(actual_dot)

            x_right = actual_dot.x() - 1

            def add_to_stack_new_start_dot():
                while actual_dot.x() <= x_right:
                    flag = False
                    color = self._image.pixelColor(actual_dot)

                    while actual_dot.x() <= x_right and color != self._pen_color and color != self._fill_color:
                        if flag == False:
                            flag = True

                        actual_dot.setX(actual_dot.x() + 1)
                        color = self._image.pixelColor(actual_dot)

                    if flag == True:
                        color = self._image.pixelColor(actual_dot)

                        if actual_dot.x() == x_right and color != self._pen_color and color != self._fill_color:
                            stack.append(deepcopy(actual_dot))
                        else:
                            buffer = deepcopy(actual_dot)
                            buffer.setX(actual_dot.x() - 1)
                            stack.append(deepcopy(buffer))

                    x_in = actual_dot.x()
                    color = self._image.pixelColor(actual_dot)

                    while color == self._pen_color or color == self._fill_color and actual_dot.x() < x_right:
                        actual_dot.setX(actual_dot.x() + 1)
                        color = self._image.pixelColor(actual_dot)

                    if actual_dot.x() == x_in:
                        actual_dot.setX(actual_dot.x() + 1)

            actual_dot.setX(x_left)

            if actual_dot.y() - 1 >= 1:
                actual_dot.setY(actual_dot.y() - 1)
                add_to_stack_new_start_dot()

            actual_dot.setX(x_left)

            if actual_dot.y() + 2 < self._image.height():
                actual_dot.setY(actual_dot.y() + 2)
                add_to_stack_new_start_dot()

            if has_delay:
                if has_delay:
                    loop = QEventLoop()
                    QTimer.singleShot(50, loop.quit)
                    loop.exec()


    def _draw_point(self, dot: QPoint):
        self._image.setPixelColor(dot, self._fill_color)

        self.update()

    def _check_event(self, ev):
        if ev.button() != Qt.LeftButton:
            return 0
        if self.rect().contains(ev.x(), ev.y()):
            return 1
        return 0

    def change_point_select_status(self):
        self._actual_draw_point_status = not self._actual_draw_point_status

    def add_point(self, dot: QPoint):
        painter = QPainter(self._image)
        pen = QPen()

        if not self._actual_draw_point_status:
            pen.setColor(self._pen_color)

        painter.setPen(pen)

        if not self._actual_draw_point_status and self._actual_figure is None:
            self._actual_figure = Figure(dot)
        elif not self._actual_draw_point_status:
            painter.drawLine(self._actual_figure.get_actual_point(), dot)
            self._actual_figure.add_point(dot)

            if self._actual_figure.get_start_point() == dot:
                del self._actual_figure
                self._actual_figure = None
        if self._actual_draw_point_status:
            self._actual_start = dot

        painter.setPen(pen)

        if not self._actual_draw_point_status:
            painter.drawPoint(dot)

        painter.end()

        self.update()

    def draw_ellipse(self, dot: QPoint, a: float, b: float):
        painter = QPainter(self._image)
        pen = QPen()
        pen.setColor(self._pen_color)
        painter.setPen(pen)
        painter.drawEllipse(dot, a, b)
        painter.end()
        self.update()

    def mousePressEvent(self, ev):
        if self._check_event(ev) == 1:
            ev.accept()
            dot = QPoint(ev.x(), ev.y())
            self.add_point(dot)

    def clean(self):
        self._image.fill(Qt.transparent)
        self._actual_figure = None
        self._actual_start = None
        self.update()
