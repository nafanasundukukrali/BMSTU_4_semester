from PySide6.QtWidgets import QFrame
from PySide6.QtGui import QFont, QPainter, QPen, QColor


class PaintField(QFrame):
    def __init__(self, parent, params, figure):
        super().__init__(parent)
        self._figure = figure
        self._labelFont = QFont("Times", 15, QFont.Bold)
        self.setFixedSize(*params)
        self.setStyleSheet("background: white")
        self.reverse_action = []

    def paintEvent(self, event):
        super().paintEvent(event)
        self._painter = QPainter(self)
        self._painter.setFont(self._labelFont)
        pen = QPen()
        pen.setColor(QColor(120, 0, 0))
        self._painter.setPen(pen)

        if not self._figure.check_free_status():
            self._draw_body()

        self._painter.end()

    def _draw_body(self):
        self._painter.save()
        self._painter.restore()
        self._draw_polyline_by_dots(self._figure.get_body_rect())
        self._draw_polyline_by_dots(self._figure.get_header())
        self._draw_polyline_by_dots(self._figure.get_tube())
        self._draw_polyline_by_dots(self._figure.get_wheels_base())

        for circle in self._figure.get_wheels():
            self._draw_polyline_by_dots(circle)

    def _draw_polyline_by_dots(self, array):
        for i in range(1, len(array)):
            self._painter.drawLine(array[i - 1][0], array[i - 1][1],
                                   array[i][0], array[i][1])