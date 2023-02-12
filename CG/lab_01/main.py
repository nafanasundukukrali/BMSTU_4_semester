import sys
from config import *
from ResultWindow import ResultWindow

from PySide6.QtWidgets import (QApplication,
                               QLabel,
                               QLineEdit,
                               QListWidgetItem, 
                               QMainWindow, 
                               QPushButton,
                               QGridLayout,
                               QVBoxLayout,
                               QWidget,
                               QListWidget,
                               QHBoxLayout,
                               )


class InputCoordsWidget(QWidget):
    def __init__(self):
        super().__init__()

        self._x = QLineEdit(self)
        self._y = QLineEdit(self)

        self._layout = QHBoxLayout(self)
        self._layout.addWidget(QLabel("x"))
        self._layout.addWidget(self._x)
        self._layout.addWidget(QLabel("y"))
        self._layout.addWidget(self._y)
    
    def checkInputData(self):
        if (not self.checkNumberInString(self._x.text()) or not
                self.checkNumberInString(self._y.text())):
            MessageDisplay(self, INPUT_RULES, "Некорректный ввод")

            return []
        else:
            return [self._x.text(), self._y.text()]

    @staticmethod
    def checkNumberInString(string):
        try:
            float(string)
            return True
        except:
            return False

class DotWidget(QWidget):
    plentlyNumber = 0

    def __init__(self):
        super().__init__()

        DotWidget.plentlyNumber += 1

        self._listWidget = QListWidget()

        self._addButton = QPushButton("Добавить новую точку", self)
        self._inputWidget = InputCoordsWidget()
        self._removeButton = QPushButton("Удалить выбранную точку", self)

        self._addButton.clicked.connect(self._addItemByClick)
        self._removeButton.clicked.connect(self._removeListItemByClick)

        self._layout = QVBoxLayout(self) 

        self._layout.addWidget(QLabel(f'Список введённых точек множества номер {DotWidget.plentlyNumber}'))
        self._layout.addWidget(self._listWidget)
        self._layout.addWidget(self._addButton)
        self._layout.addWidget(QLabel(f'Координаты новой точки. {INPUT_RULES}'))
        self._layout.addWidget(self._inputWidget)
        self._layout.addWidget(self._removeButton)

    def _removeListItemByClick(self):
        if not self._listWidget.currentItem():
            MessageDisplay(self, "Не выбран ни один элемент из списка, или список пуст.", "Некорректный ввод")
        else:
            self._listWidget.takeItem(self._listWidget.row(self._listWidget.currentItem()))

    def _addItemByClick(self):
        value = self._inputWidget.checkInputData()
        
        if value == []:
            return

        newItem = QListWidgetItem()
        newItem.setText(f'({value[0]};{value[1]})')
        # newItem.setData(QtGui.QtRop, value)

        self._listWidget.addItem(newItem)
    
    def getCoordsList(self):
        items = []

        for i in range(self._listWidget.count()):
            value = self._listWidget.item(i).text()
            value = list(map(float, value[1:][:len(value) - 2].split(';')))
            items.append(value)

        return items


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        grid = QGridLayout()
        widget = QWidget()
        widget.setLayout(grid)

        self._firstDotWiget = DotWidget()
        grid.addWidget(self._firstDotWiget, 0, 0)

        self._solveTaskButton = QPushButton("Показать решение", self)
        self._solveTaskButton.clicked.connect(self._displayResult)
        grid.addWidget(self._solveTaskButton, 1, 0, 1, 2)

        self._secondDotWiget = DotWidget()
        grid.addWidget(self._secondDotWiget, 0, 1)

        self.setCentralWidget(widget)
        self.initGUI()
    
    
    def initGUI(self):
        self.setWindowTitle('Конкина Алина, ЛР1')
        self.setMinimumHeight(600)
        self.moveToCenter()
        self.show()

    def moveToCenter(self):
        qr = self.frameGeometry()
        cp = self.screen().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

    def _displayResult(self):
        firstData = self._firstDotWiget.getCoordsList()
        secondData = self._firstDotWiget.getCoordsList()

        if not firstData or not secondData:
            MessageDisplay(self, "В обоих множествах отсуствуют данные.")
            return

        self._resultWindow = ResultWindow(firstData, secondData)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    app.exec()
