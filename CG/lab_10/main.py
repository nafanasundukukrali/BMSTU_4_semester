from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPainter, QBrush, QPen, QPixmap, QPalette, QColor, QImage
from PyQt5.QtCore import QCoreApplication, QEventLoop, Qt, QPointF, QRectF
from PyQt5.QtWidgets import QMessageBox, QMainWindow, QGraphicsScene

import sys
import lab_10_ui
from screen_image import ScreenImage
from math import cos, sin, pi, fabs, exp
from typing import List
from functions import *
from copy import deepcopy

FUNCTIONS = ['cos(x) * sin(z)', 'cos(x)', 'x + y']

class MessageDisplay(QMessageBox):
    def __init__(self, base, messageText, messageHeader="Ошибка", messageType="Warning"):
        super().__init__(base)

        if messageHeader:
            self.setWindowTitle(messageHeader)

        if messageType == "Warning":
            self.set_warning_message_icon()

        self.setText(messageText)
        self.exec()

    def set_warning_message_icon(self):
        self.setIcon(QMessageBox.Warning)

class MainWindow(QMainWindow, lab_10_ui.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.screenImage = ScreenImage()
        self.function = ''
        self.bordersX = [0.0, 0.0]
        self.bordersZ = [0.0, 0.0]
        self.stepX = 0; self.stepZ = 0
        self.angles = [0.0, 0.0, 0.0]
        self.timerId = 0

        self.setupUi(self)

        self.addChooseFunctions()
        self.addToUI()
        self.show()

    def addToUI(self):
        self.but_draw_on_screen.clicked.connect(self.draw3dSurface)
        self.but_clean_all.clicked.connect(self.cleanAll)

        self.screenImage.setSceneRect(0, 0, self.width(), self.height())
        self.graphicsView.setScene(self.screenImage)
        self.graphicsView.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.graphicsView.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff)

    def addChooseFunctions(self):
        self.box_functions.addItem(FUNCTIONS[0])
        self.box_functions.addItem(FUNCTIONS[1])
        self.box_functions.addItem(FUNCTIONS[2])

    def cleanAll(self):
        self.screenImage.clear()

    def draw3dSurface(self):
        self.screenImage.clear()
        functions = [f1, f2, f3]
        return_d = self.getData()

        if type(return_d) == MessageDisplay:
            return

        indexFunction = self.getIndexFunction()
        self.drawFloatingHorizon(functions[indexFunction], self.bordersX, self.bordersZ,
                                   self.stepX, self.stepZ, self.angles, int(self.screenImage.width()), int(self.screenImage.height()))

    def getData(self):
        self.function = self.box_functions.currentText()

        buffer = self.spinbox_start_x.text()

        try:
            self.bordersX[0] = float(buffer)
        except Exception:
            return QMessageBox(self, "Данные введены некорректно.")

        buffer = self.spinbox_end_x.text()

        try:
            self.bordersX[1] = float(buffer)
        except Exception:
            return QMessageBox(self, "Данные введены некорректно.")


        buffer = self.spinbox_start_z.text()

        try:
            self.bordersZ[0] = float(buffer)
        except Exception:
            return QMessageBox(self, "Данные введены некорректно.")

        buffer = self.spinbox_end_z.text()

        try:
            self.bordersZ[1] = float(buffer)
        except Exception:
            return QMessageBox(self, "Данные введены некорректно.")

        buffer = self.spinbox_step_x.text()

        try:
            self.stepX = float(buffer)
        except Exception:
            return QMessageBox(self, "Данные введены некорректно.")

        buffer = self.spinbox_step_z.text()

        try:
            self.stepZ = float(buffer)
        except Exception:
            return MessageDisplay(self, "Данные введены некорректно.")

        buffer = self.spinbox_rotate_x.text()

        try:
            self.angles[0] = float(buffer)
        except Exception:
            return MessageDisplay(self, "Данные введены некорректно.")

        buffer = self.spinbox_rotate_y.text()

        try:
            self.angles[1] = float(buffer)
        except Exception:
            return MessageDisplay(self, "Данные введены некорректно.")

        buffer = self.spinbox_rotate_z.text()

        try:
            self.angles[2] = float(buffer)
        except Exception:
            return MessageDisplay(self, "Данные введены некорректно.")

    def getIndexFunction(self):
        indexFunction = -1
        for i in range(len(FUNCTIONS)):
            if FUNCTIONS[i] == self.function:
                indexFunction = i
                break
        return indexFunction

    def drawFloatingHorizon(self, function: str, bordersX: List[int], bordersZ: List[int],
                                    stepX: int, stepZ: int, angles: List[int], widthScreen, heightScreen):
        leftX, rightX = None, -1
        leftY, rightY = None, -1

        top = [0] * widthScreen
        bottom = [heightScreen] * widthScreen

        maxZ = bordersZ[1]; minZ = bordersZ[0]; stepZ = stepZ
        maxX = bordersX[1]; minX = bordersX[0]; stepX = stepX

        z = maxZ
        while z >= minZ - stepZ / 2:
            prevX = minX
            prevY = function(minX, z)
            prevX, prevY = self.to2d(prevX, prevY, z, angles)
            leftX, leftY = self.processSideEdge(prevX, prevY,
                                                    leftX, leftY, top, bottom)
            prevVisibleFlag = self.visible(prevX, prevY, top, bottom)
            x = minX
            while x <= maxX + stepX / 2:
                curY = function(x, z)
                curX, curY = self.to2d(x, curY, z, angles)
                curVisibleFlag = self.visible(curX, curY, top, bottom)
                if curVisibleFlag == prevVisibleFlag:
                    if curVisibleFlag == 1 or curVisibleFlag == -1:
                        self.screenImage.lineDraw(prevX, prevY, curX, curY)
                        self.horizont(prevX, prevY, curX, curY,
                                      top, bottom)
                else:
                    if curVisibleFlag == 0:
                        if prevVisibleFlag == 1:
                            xi, yi = self.intersection(prevX, prevY,
                                                       curX, curY, top)
                        else:
                            xi, yi = self.intersection(prevX, prevY,
                                                       curX, curY, bottom)
                        self.screenImage.lineDraw(prevX, prevY, xi, yi)
                        self.horizont(prevX, prevY, xi, yi, top, bottom)
                    else:
                        if curVisibleFlag == 1:
                            if prevVisibleFlag == 0:
                                xi, yi = self.intersection(prevX, prevY,
                                                            curX, curY,
                                                            top)
                                self.screenImage.lineDraw(xi, yi, curX, curY)
                                self.horizont(xi, yi, curX, curY, top, bottom)
                            else:
                                xi, yi = self.intersection(prevX, prevY,
                                                            curX, curY,
                                                            bottom)
                                self.screenImage.lineDraw(prevX, prevY, xi, yi)
                                self.horizont(prevX, prevY, xi, yi, top, bottom)
                                xi, yi = self.intersection(prevX, prevY,
                                                            curX, curY,
                                                            top)
                                self.screenImage.lineDraw(xi, yi, curX, curY)
                                self.horizont(xi, yi, curX, curY, top, bottom)
                        else:
                            if prevVisibleFlag == 0:
                                xi, yi = self.intersection(prevX, prevY,
                                                           curX, curY,
                                                           bottom)
                                self.screenImage.lineDraw(xi, yi, curX, curY)
                                self.horizont(xi, yi, curX, curY, top, bottom)
                            else:
                                xi, yi = self.intersection(prevX, prevY, 
                                                           curX, curY,
                                                           top)
                                self.screenImage.lineDraw(prevX, prevY, xi, yi)
                                self.horizont(prevX, prevY, xi, yi,
                                              top, bottom)
                                xi, yi = self.intersection(prevX, prevY,
                                                           curX, curY,
                                                           bottom)
                                self.screenImage.lineDraw(xi, yi, curX, curY)
                                self.horizont(xi, yi, curX, curY, top, bottom)
                prevVisibleFlag = curVisibleFlag
                prevX = curX; prevY = curY
                x += stepX
            rightX, rightY = self.processSideEdge(prevX, prevY, rightX, 
                                                      rightY, top, bottom)
            z -= stepZ
            QCoreApplication.processEvents(QtCore.QEventLoop.ExcludeUserInputEvents, 5)
                                                       

    def processSideEdge(self, prevX: int, prevY: int, edgeX: int, edgeY: int, top, bottom):
        if edgeX is not None:
            self.screenImage.lineDraw(edgeX, edgeY, prevX, prevY)
            self.horizont(edgeX, edgeY, prevX, prevY, top, bottom)
        edgeX = prevX; edgeY = prevY
        return edgeX, edgeY

    def horizont(self, x1: int, y1: int, x2: int, y2: int, top: List[int], bottom: List[int]):
        if (x2 - x1) == 0:
            top[x2] = max(top[x2], y2)
            bottom[x2] = min(bottom[x2], y2)
        else:
            m = (y2 - y1) / (x2 - x1)
            for x in range(x1, x2 + 1):
                y = round(m * (x - x1) + y1)
                top[x] = max(top[x], y)
                bottom[x] = min(bottom[x], y)
        return      

    def visible(self, x: int, y: int, top: List[int], bottom: List[int]):
        curVisibleFlag = 0
        if y < top[x] and y > bottom[x]:
            curVisibleFlag = 0
        elif y >= top[x]:
            curVisibleFlag = 1
        elif y <= bottom[x]:
            curVisibleFlag = -1
        return curVisibleFlag

    def intersection(self, x1, y1, x2, y2, array):
        dx = x2 - x1
        if dx == 0:
            xi = x2
            yi = array[x2]
        elif y1 == array[x1] and y2 == array[x2]:
            xi = x2; yi = array[x2]
        else:
            dcurY = y2 - y1
            dprevY = array[x2] - array[x1]
            m = dcurY / dx
            xi = x1 -int((dx * (y1 - array[x1]) / (dcurY - dprevY)))
            yi = int(m * (xi - x1) + y1)

        return xi, yi

    def sign(self, x: int):
        sign = 0
        if x < 0:
            sign = -1
        elif x > 0:
            sign = 1
        return sign


    def to2d(self, x: int, y: int, z: int, angles: List[int]):
        x, y = self.rotateX(x, y, z, angles[0])
        x, y = self.rotateY(x, y, z, angles[1])
        x, y = self.rotateZ(x, y, z, angles[2])
        return self.scale(x, y)

    def rotateX(self, x: int, y: int, z: int, angle: int):
        angleX = self.degToRad(angle)
        y = y * cos(angleX) - z * sin(angleX)
        return x, y

    def rotateY(self, x: int, y: int, z: int, angle: int):
        angleY = self.degToRad(angle)
        x = x * cos(angleY) - z * sin(angleY)
        return x, y

    def rotateZ(self, x: int, y: int, z: int, angle: int):
        angleZ = self.degToRad(angle)
        buffer_x = x

        x = cos(angleZ) * x - sin(angleZ) * y
        y = cos(angleZ) * y + sin(angleZ) * buffer_x
        return x, y

    def degToRad(self, angle):
        return pi / 180 * angle

    def scale(self, x, y):
        x *= 50; y *= 50
        x += self.screenImage.width() // 2; y += self.screenImage.height() // 2
        return int(x), int(y)

if __name__ == "__main__":  
    app = QtWidgets.QApplication(sys.argv)
    main_window = MainWindow()
    main_window.setWindowState(Qt.WindowMaximized)
    main_window.setStyleSheet("* {font-size: 14pt}")
    sys.exit(app.exec_())