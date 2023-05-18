from PySide6.QtWidgets import (QWidget, QPushButton, QVBoxLayout, QHBoxLayout, QLabel, QFrame, QRadioButton,
                               QButtonGroup)
from PySide6.QtGui import QFont, Qt, QGuiApplication, QColor

from config import MessageDisplay, TASK
from ColorSelectionField import ColorSelectionField
from InputTwoParams import InputTwoParams


class ControlField(QWidget):
    MINWIDTH = 450
    cords_text = "Координаты центра: "
    cords_zero_status = "Пока не определены"
    start_of_last_action_status = "Отмена последнего преобразования"

    def __init__(self, parent,
                 draw_action,
                 close_figure_action,
                 add_point_action,
                 change_background_color_action,
                 change_pen_color_action,
                 change_fill_color,
                 clean_action):
        super().__init__(parent)
        self._add_point_action = add_point_action
        self._draw_action = draw_action
        self._parent = parent
        self.setStyleSheet('QPushButton {background-color: rgb(0,153,51)}')
        self.setMinimumWidth(self.MINWIDTH)
        self._layout = QVBoxLayout()
        self._layout.setStretch(0, 4)

        self._fill_color_widget = ColorSelectionField(self, "  Выбрать цвет закраски  ", self.width(), change_fill_color, QColor(0, 0, 0))
        self._layout.addWidget(self._fill_color_widget)

        self._edges_color_widget = ColorSelectionField(self, "  Выбрать цвет рёбер  ", self.width(), change_pen_color_action, QColor(0, 0, 0))
        self._layout.addWidget(self._edges_color_widget)

        self._background_color_widget = ColorSelectionField(self, "  Выбрать цвет фона  ", self.width(), change_background_color_action)
        self._layout.addWidget(self._background_color_widget)

        self._label_circle = self._generate_block_label("Режим закраски:")
        self._layout.addWidget(self._label_circle)

        self._radio_button_1 = QRadioButton('С задержкой')

        self._radio_button_2 = QRadioButton('Без задержки')
        self._radio_button_2.setChecked(True)

        self._button_group = QButtonGroup()
        self._button_group.addButton(self._radio_button_1)
        self._button_group.addButton(self._radio_button_2)

        self._layout.addWidget(self._radio_button_1)
        self._layout.addWidget(self._radio_button_2)

        self._dot_co_ords = InputTwoParams(self, "Координаты точки: ")
        self._layout.addWidget(self._dot_co_ords)
        self._add_point_button = QPushButton("Добавить новую точку")
        self._add_point_button.clicked.connect(self._add_point)
        self._layout.addWidget(self._add_point_button)

        self._concatate_button = QPushButton("Замкнуть многоугольник")
        self._concatate_button.clicked.connect(close_figure_action)
        self._layout.addWidget(self._concatate_button)

        self._fill_button = QPushButton("Выполнить закраску")
        self._fill_button.clicked.connect(self._fill)
        self._layout.addWidget(self._fill_button)

        self._clear = QPushButton("Очистить экран")
        self._clear.clicked.connect(clean_action)

        self._task = QPushButton("Задание")
        self._task.clicked.connect(self._print_task)

        self._layout.addWidget(self._clear)
        self._layout.addWidget(self._task)
        self.setLayout(self._layout)

    def _print_task(self):
        return MessageDisplay(self, messageText=TASK, messageHeader="Задание", messageType="Info")

    @staticmethod
    def _generate_block_label(text):
        label_field = QLabel(text)

        font = QFont()
        font.setBold(True)
        font.setUnderline(True)

        label_field.setFont(font)

        return label_field

    def _add_point(self):
        data = self._dot_co_ords.get_data()

        if data == None:
            return MessageDisplay(self, "Некорректно указаны или отсуствуют данные о координатах новой точки.")

        self._add_point_action(data)

    def _fill(self):
        delay_status = self._radio_button_1.isChecked()

        self._draw_action(delay_status)
