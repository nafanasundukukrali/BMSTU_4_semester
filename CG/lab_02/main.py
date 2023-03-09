import sys
from PySide6.QtWidgets import (QMainWindow, QApplication, QHBoxLayout, QWidget)
from PySide6.QtGui import QGuiApplication
from Figure import Figure
from PaintField import PaintField
from ControlField import ControlField


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        widget = QWidget()
        self._layout = QHBoxLayout()
        self._figure = Figure()
        self._ps = QGuiApplication.primaryScreen()
        self._paintField = PaintField(self, [self._ps.geometry().width() * 0.6,
                                             self._ps.geometry().height() * 0.85], self._figure)
        control_field = ControlField(self._update_figure_action, self._restart_figure_action, self._figure)
        self._layout.addWidget(control_field)
        self._layout.addWidget(self._paintField)
        widget.setLayout(self._layout)
        self.setCentralWidget(widget)
        self.center()
        self.show()

    def _update_figure_action(self):
        self._paintField.update()

    def _restart_figure_action(self):
        self._figure.draw_base_figure(self._ps.geometry().width() * 0.6 / 2, self._ps.geometry().height() * 0.85 / 2)
        self._update_figure_action()

    def center(self):
        qr = self.frameGeometry()
        cp = QGuiApplication.primaryScreen().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.setWindowTitle("ЛР №2, Конкина Алина, ИУ7-43Б")
    window.setStyleSheet("* {font-size: 14pt}")
    app.exec()
