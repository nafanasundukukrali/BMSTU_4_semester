import math
import subprocess
from PySide6.QtWidgets import (QMainWindow, QHBoxLayout, QWidget)
from PySide6.QtGui import QGuiApplication, QColor
from PySide6.QtCore import QPoint
from PaintField import PaintField
from ControlField import ControlField


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        widget = QWidget()
        self._layout = QHBoxLayout()
        self._ps = QGuiApplication.primaryScreen()
        self._paintField = PaintField([self._ps.geometry().width() * 0.6, self._ps.geometry().height() * 0.85])
        control_field = ControlField(self, self._draw_circle_or_ellipse, self._draw_spec, self._paintField.clean)
        self._layout.addWidget(control_field)
        self._layout.addWidget(self._paintField)
        widget.setLayout(self._layout)
        self.setCentralWidget(widget)
        self.center()
        self.show()

    def _draw_circle_or_ellipse(self, algorithms, center: QPoint, a: float, b: float, pen_color: QColor = None,
                                background_color: QColor = None, is_circle=False, time_analyze=False):

        if is_circle:
            values = algorithms[0](center, a, time_analyzer=time_analyze)
        else:
            values = algorithms[1](center, a, b, time_analyzer=time_analyze)

        if time_analyze:
            return values

        self._paintField.draw_new_dots(values, background_color, pen_color)

    @staticmethod
    def _rotate_point(dot, xc, yc, alpha):
        def convert_cords_to_radian():
            return alpha * math.pi / 180

        alpha = convert_cords_to_radian()

        dot_1 = []

        dot_1.append(round(xc + (dot[0] - xc) * math.cos(alpha) + (dot[1] - yc) * math.sin(alpha)))
        dot_1.append(round(yc - (dot[0] - xc) * math.sin(alpha) + (dot[1] - yc) * math.cos(alpha)))

        return dot_1

    def _draw_spec(self, algorithm, step, count, a, b, pen_color: QColor = None,
                   background_color: QColor = None, time_analyze=False, is_circle=False):
        field_params = self._paintField.size()
        x0 = field_params.width()
        y0 = field_params.height()
        center = QPoint(x0 // 2, y0 // 2)

        if a > b:
            e = (a ** 2 - b ** 2) ** 0.5 / b
        else:
            e = (b ** 2 - a ** 2) ** 0.5 / a

        values = []

        for i in range(count):
            values.append(self._draw_circle_or_ellipse(algorithm, center, a, b, pen_color=pen_color,
                                                       background_color=background_color,
                                                       time_analyze=time_analyze, is_circle=is_circle))

            if a > b:
                b += step
                a = ((e * b) ** 2 + b ** 2) ** 0.5
            else:
                a += step
                b = ((e * a) ** 2 + a ** 2) ** 0.5

        if time_analyze:
            return values

    def center(self):
        qr = self.frameGeometry()
        cp = QGuiApplication.primaryScreen().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())
        self.setFixedSize(QGuiApplication.primaryScreen().availableGeometry().normalized().size())

        import subprocess

        cmd = ['xrandr']
        cmd2 = ['grep', '*']
        p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
        p2 = subprocess.Popen(cmd2, stdin=p.stdout, stdout=subprocess.PIPE)
        p.stdout.close()

        resolution_string, junk = p2.communicate()
        resolution = resolution_string.split()[0]
        width, height = resolution.decode().split('x')

        self.setFixedSize(int(int(width) * 0.96), int(int(height) * 0.96))
