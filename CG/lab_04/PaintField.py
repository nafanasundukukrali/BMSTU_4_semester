from PySide6.QtWidgets import QFrame
from PySide6.QtGui import QFont, QPainter, QPen, QColor, QPixmap
from PySide6.QtCore import QPoint, Qt


class PaintField(QFrame):
    def __init__(self, params):
        super().__init__()
        self._labelFont = QFont("Times", 15, QFont.Bold)
        self.setFont(QFont("Times", 15, QFont.Bold))
        self.setFixedSize(*params)
        self._background = QPixmap(self.size())
        self._image = QPixmap(self.size())
        self._pen_color = QColor(0, 0, 0)
        self._background_color = QColor(0, 0, 0)
        self._background.fill(self._background_color)
        self._image.fill(Qt.transparent)
        self._newData = []

    def paintEvent(self, event):
        super().paintEvent(event)
        painter = QPainter(self)
        painter.drawPixmap(QPoint(), self._background)
        painter.drawPixmap(QPoint(), self._image)

    def _draw_data(self):
        painter = QPainter(self._image)

        pen = QPen()
        pen.setColor(self._pen_color)
        painter.setPen(pen)

        for item in self._newData:
            if type(item[0]) == QPoint and len(item) > 1:
                self._pen_color.setAlpha(item[1])
                pen.setColor(self._pen_color)
                painter.setPen(pen)

            if type(item[0]) == QPoint:
                painter.drawPoint(item[0])
            else:
                painter.drawEllipse(item[0], item[1], item[2], item[3])

        painter.end()

        self.update()
        self._newData = []

    def draw_new_dots(self, data, background_color, pen_color):
        self._newData = data

        if pen_color != self._pen_color:
            self._pen_color = pen_color

        if background_color != self._background_color:
            self._background_color = background_color
            self._background.fill(self._background_color)

        self._draw_data()

    def clean(self):
        self._image.fill(Qt.transparent)
        self.update()
