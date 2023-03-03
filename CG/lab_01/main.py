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
                               QAbstractItemView
                               )


class InputCordsWidget(QWidget):
    def __init__(self):
        super().__init__()

        self._x = QLineEdit(self)
        self._y = QLineEdit(self)

        self._layout = QHBoxLayout(self)
        self._layout.addWidget(QLabel("x"))
        self._layout.addWidget(self._x)
        self._layout.addWidget(QLabel("y"))
        self._layout.addWidget(self._y)

    def check_input_data(self):
        if (not self.check_number_in_string(self._x.text()) or not
        self.check_number_in_string(self._y.text())):
            MessageDisplay(self, INPUT_RULES, "Некорректный ввод")

            return []
        else:
            return [self._x.text(), self._y.text()]

    @staticmethod
    def check_number_in_string(string):
        try:
            float(string)
            return True
        except Exception:
            return False


class DotWidget(QWidget):
    plentyNumber = 0

    def __init__(self):
        super().__init__()

        DotWidget.plentyNumber += 1

        self._actualChangeFlag = False
        self._lastChangeBuffer = ""
        self._defaultAddButtonName = "Добавить новую точку"
        self._defaultChangeButtonName = "Изменить выбранную точку"
        self._selectedItem = None

        self._listWidget = QListWidget()

        self._addButton = QPushButton("Добавить новую точку", self)
        self._inputWidget = InputCordsWidget()
        self._changeButton = QPushButton("Изменить выбранную точку", self)
        self._removeButton = QPushButton("Удалить выбранную точку", self)

        self._addButton.clicked.connect(self._add_item_by_click)
        self._changeButton.clicked.connect(self._change_item_by_click)
        self._removeButton.clicked.connect(self._remove_list_item_by_click)

        self._layout = QVBoxLayout(self)

        self._layout.addWidget(QLabel(f'Список введённых точек множества номер {DotWidget.plentyNumber}'))
        self._layout.addWidget(self._listWidget)
        self._layout.addWidget(self._addButton)
        self._layout.addWidget(QLabel(f'Координаты новой точки. {INPUT_RULES}'))
        self._layout.addWidget(self._inputWidget)
        self._layout.addWidget(self._changeButton)
        self._layout.addWidget(self._removeButton)

    def _change_item_selection_mode(self):
        if self._actualChangeFlag:
            self._listWidget.setSelectionMode(QAbstractItemView.SelectionMode.NoSelection)
        else:
            self._listWidget.setSelectionMode(QAbstractItemView.SelectionMode.SingleSelection)

    def _remove_list_item_by_click(self):
        if self._actualChangeFlag:
            MessageDisplay(self, "Отмените или сохраните изменения, чтобы удалить кнопку.", "Изменение координаты точки")
        elif not self._listWidget.currentItem():
            MessageDisplay(self, "Не выбран ни один элемент из списка, или список пуст.", "Некорректный ввод")
        else:
            self._listWidget.takeItem(self._listWidget.row(self._listWidget.currentItem()))

    def _add_item_by_click(self):
        value = self._inputWidget.check_input_data()

        if not value:
            return

        if self._actualChangeFlag:
            self._changeButton.setText(self._defaultChangeButtonName)
            self._addButton.setText(self._defaultAddButtonName)
            self._selectedItem.setText(f'({value[0]};{value[1]})')
            self._actualChangeFlag = not self._actualChangeFlag
            self._change_item_selection_mode()
        else:
            new_item = QListWidgetItem()
            new_item.setText(f'({value[0]};{value[1]})')

            self._listWidget.addItem(new_item)

    def _change_item_by_click(self):
        if not self._listWidget.currentItem():
            MessageDisplay(self, "Не выбран ни один элемент из списка, или список пуст.", "Некорректный ввод")
            return

        self._actualChangeFlag = not self._actualChangeFlag

        if not self._actualChangeFlag:
            self._changeButton.setText(self._defaultChangeButtonName)
            self._addButton.setText(self._defaultAddButtonName)
            self._selectedItem.setText(self._lastChangeBuffer)
        else:
            self._lastChangeBuffer = self._listWidget.currentItem().text()
            self._listWidget.currentItem().setText("Введите новые координаты в полях ввода")
            self._changeButton.setText("Отменить изменения без сохранения")
            self._addButton.setText("Сохранить изменения")
            self._selectedItem = self._listWidget.currentItem()

        self._change_item_selection_mode()

    def get_cords_list(self):
        items = []

        for i in range(self._listWidget.count()):
            value = self._listWidget.item(i).text()
            value = list(map(float, value[1:][:len(value) - 2].split(';')))
            items.append(value)

        return items


class MainWindow(QMainWindow):
    def __init__(self, screen_params):
        super().__init__()
        self._screenParams = screen_params.size()
        grid = QGridLayout()
        widget = QWidget()
        widget.setLayout(grid)

        self._firstDotWidget = DotWidget()
        grid.addWidget(self._firstDotWidget, 0, 0)

        self._solveTaskButton = QPushButton("Показать решение", self)
        self._solveTaskButton.clicked.connect(self._display_result)
        grid.addWidget(self._solveTaskButton, 1, 0, 1, 2)

        self._secondDotWidget = DotWidget()
        grid.addWidget(self._secondDotWidget, 0, 1)

        self.setCentralWidget(widget)
        self.init_gui()

    def init_gui(self):
        self.setWindowTitle('Конкина Алина, ЛР1')
        self.setMinimumHeight(600)
        self.move(self._screenParams.width() // 2, self._screenParams.height())
        self.show()

    def move_to_center(self):
        qr = self.frameGeometry()
        cp = self.screen().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

    def _display_result(self):
        firstData = self._firstDotWidget.get_cords_list()
        secondData = self._secondDotWidget.get_cords_list()

        # firstData = [
        #     [1, 3], [-1, 5], [3, 5],
        #     [4, 0], [3, 1], [5, 1],
        #     [6, 7], [49, 5], [14, 3],
        #     [6, 7], [49, 5], [14, 3],
        #     [5, -1], [7, -3], [5, -5],
        # ]

        # secondData = [
        #     [9, 3], [7, 3], [11, 3],
        #     [10, 4], [9, 5], [10, 6],
        #     [14, 3], [11, 7], [14, 9],
        # ]

        # for i in range(len(firstData)):
        #     firstData[i][0] *= -1/1000
        #     firstData[i][1] *= 1/1000
        #
        # for i in range(len(secondData)):
        #     secondData[i][0] *= -1/1000
        #     secondData[i][1] *= 1/1000

        if not firstData and not secondData:
            MessageDisplay(self, "В обоих множествах отсуствуют данные.")
            return
        self._resultWindow = ResultWindow(self, firstData, secondData, self._screenParams)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow(app.primaryScreen())
    app.exec()
