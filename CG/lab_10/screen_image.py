from PyQt5.QtWidgets import QMainWindow, QGraphicsScene
from PyQt5.QtGui import QPen
from PyQt5.QtCore import Qt

import lab_10_ui

class ScreenImage(QGraphicsScene, QMainWindow, lab_10_ui.Ui_MainWindow):
    def __init__(self):
        '''
        Конструктор
        '''
        super().__init__()
        self.pen_graph = QPen(Qt.black)

    def lineDraw(self, x1, y1, x2, y2):
        self.addLine(x1, y1, x2, y2, self.pen_graph)
