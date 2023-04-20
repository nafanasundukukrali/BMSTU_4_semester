from PySide6.QtWidgets import (QWidget, QPushButton, QGridLayout, QLabel, QTextEdit)
from PySide6.QtGui import QFont
from PySide6.QtCore import Qt
from config import MessageDisplay


class InputField(QWidget):
    _field_type = {
        'move': {
            'name': 'Перенос',
            'widget_count': 1,
            'max_sub_widget_count': 2,
            'widgets': [['Смещение по координатным осям', 'dx', 'dy']]
        },
        'scale': {
            'name': 'Масштабирование',
            'widget_count': 2,
            'max_sub_widget_count': 2,
            'widgets': [
                ['Координаты центра масштабирования', 'xm', 'ym'],
                ['Коэффициенты масштабирования', 'kx', 'ky']
            ]
        },
        'rotate': {
            'name': 'Поворот',
            'widget_count': 2,
            'max_sub_widget_count': 2,
            'widgets': [
                ['Координаты центра поворота', 'xc', 'yc'],
                ['Угол поворота', 'α, градусы']
            ]
        }
    }

    def __init__(self, parent, button_action, widget_type='move'):
        super().__init__(parent)
        self._parent = parent
        self._button_action = button_action
        self._widget_type = widget_type
        params = self._field_type[widget_type]
        grid = QGridLayout()
        self.setLayout(grid)
        grid.setColumnStretch(0, params['max_sub_widget_count'] + 1)
        self._name = QLabel(params['name'])
        font = QFont()
        font.setBold(True)
        font.setUnderline(True)
        self._name.setFont(font)
        grid.addWidget(self._name, 0, 0, 1, params['max_sub_widget_count'] + 1)
        self._widgets = []

        for i in range(params['widget_count']):
            result = [QLabel(params['widgets'][i][0])]

            for obj in params['widgets'][i][1:]:
                result.append([QLabel(obj), QTextEdit(self)])
                result[-1][1].setFixedHeight(40)

            self._widgets.append(result)

        real_index = 1

        for i in range(len(self._widgets)):
            grid.addWidget(self._widgets[i][0], real_index, 0, 1, params['max_sub_widget_count'] + 1)

            real_index_in_row = 0
            real_index += 1

            for j in range(1, len(self._widgets[i])):
                grid.addWidget(self._widgets[i][j][0], real_index, real_index_in_row, 1, 1)
                grid.addWidget(self._widgets[i][j][1], real_index, real_index_in_row + 1, 1, 1)
                real_index_in_row += 2

            real_index += 1

        self._startButton = QPushButton(f'Выполнить преобразование: {params["name"]}')
        self._startButton.clicked.connect(self._button_click)
        grid.addWidget(self._startButton, real_index, 1, 1, params['max_sub_widget_count'] + 1)

    def _button_click(self):
        data = []

        for i in range(len(self._widgets)):
            for j in range(1, len(self._widgets[i])):
                if self._check_value_correctness(self._widgets[i][j][1].toPlainText()):
                    data.append(float(self._widgets[i][j][1].toPlainText()))
                else:
                    MessageDisplay(self, "Данные введены некорректно")
                    return

        self._button_action(self._widget_type, data)

    @staticmethod
    def _check_value_correctness(value):
        try:
            float(value)
            return True
        except Exception:
            return False