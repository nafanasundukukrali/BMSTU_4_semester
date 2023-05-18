import math
import subprocess
from config import QMessageBox, MessageDisplay
from PySide6.QtWidgets import (QMainWindow, QHBoxLayout, QWidget)
from PySide6.QtGui import QGuiApplication, QColor
from PySide6.QtCore import QPoint
from PaintField import PaintField
from ControlField import ControlField
from sys import platform


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        widget = QWidget()
        self._layout = QHBoxLayout()
        self._ps = QGuiApplication.primaryScreen()
        self._paintField = PaintField([self._ps.geometry().width() * 0.6, self._ps.geometry().height() * 0.85])
        control_field = ControlField(self,
                                     self._draw_data,
                                     self._paintField.close_figure,
                                     self._paintField.add_point,
                                     self._paintField.change_background_color,
                                     self._paintField.change_pen_color,
                                     self._paintField.change_fill_color,
                                     self._paintField.clean)
        self._layout.addWidget(control_field)
        self._layout.addWidget(self._paintField)
        widget.setLayout(self._layout)
        self.setCentralWidget(widget)
        self.center()
        self.show()

    def _draw_data(self, has_delay):
        delay, result = self._paintField.draw_data(has_delay)

        if not has_delay and result is None:
            return MessageDisplay(self, f'Время закраски: {delay}ms',
                                  messageHeader="Время закраски", messageType=None)

    def center(self):
        qr = self.frameGeometry()
        cp = QGuiApplication.primaryScreen().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())
        self.setFixedSize(QGuiApplication.primaryScreen().availableGeometry().normalized().size())

        if platform != 'win32':
            cmd = ['xrandr']
            cmd2 = ['grep', '*']
            p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
            p2 = subprocess.Popen(cmd2, stdin=p.stdout, stdout=subprocess.PIPE)
            p.stdout.close()

            resolution_string, junk = p2.communicate()
            resolution = resolution_string.split()[0]
            width, height = resolution.decode().split('x')

            self.setFixedSize(int(int(width) * 0.96), int(int(height) * 0.96))
