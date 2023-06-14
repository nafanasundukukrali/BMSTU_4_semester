from PySide6.QtWidgets import (QWidget, QPushButton, QVBoxLayout, QHBoxLayout, QLabel, QFrame, QRadioButton,
                               QButtonGroup)
from PySide6.QtGui import QFont, Qt, QGuiApplication, QColor

from config import MessageDisplay, TASK, BASE_COLORS
from ColorSelectionField import ColorSelectionField
from InputTwoParams import InputTwoParams
from OneInputField import OneInputField


class ControlField(QWidget):
    MINWIDTH = 450
    cords_text = "Координаты центра: "
    cords_zero_status = "Пока не определены"
    start_of_last_action_status = "Отмена последнего преобразования"

    def __init__(self, parent,
                 cut_action,
                 add_point_action,
                 add_splitter_action,
                 change_point_select_status,
                 change_background_color_action,
                 change_line_color_action,
                 change_splitter_color,
                 change_result_color,
                 clean_action):
        super().__init__(parent)
        self._add_splitter_action = add_splitter_action
        self._add_point_action = add_point_action
        self._draw_splitter_action = add_splitter_action
        self._cut_action = cut_action
        self._parent = parent
        self.setStyleSheet('QPushButton {background-color: rgb(0,153,51)}')
        self.setMinimumWidth(self.MINWIDTH)
        self._layout = QVBoxLayout()
        self._layout.setStretch(0, 4)

        self._splitter_color_widget = ColorSelectionField(self, "  Выбрать цвет отсекателя  ",
                                                          self.width(), change_splitter_color,
                                                          BASE_COLORS.splitter_color)
        self._layout.addWidget(self._splitter_color_widget)

        self._line_color_widget = ColorSelectionField(self, "  Выбрать цвет отрезка  ",
                                                      self.width(), change_line_color_action,
                                                      BASE_COLORS.line_color)
        self._layout.addWidget(self._line_color_widget)

        self._result_color_widget = ColorSelectionField(self, "  Выбрать цвет результата  ",
                                                        self.width(), change_result_color,
                                                        BASE_COLORS.result_color)
        self._layout.addWidget(self._result_color_widget)

        self._background_color_widget = ColorSelectionField(self, "  Выбрать цвет фона  ",
                                                            self.width(), change_background_color_action,
                                                            BASE_COLORS.background_color)
        self._layout.addWidget(self._background_color_widget)

        self._splitter_selector_button = QRadioButton('Ввод координаты отсекателя')
        self._splitter_selector_button.setChecked(True)
        self._splitter_selector_button.clicked.connect(change_point_select_status)

        self._line_selector_button = QRadioButton('Ввод данных отрезков')
        self._line_selector_button.clicked.connect(change_point_select_status)

        self._button_group_1 = QButtonGroup()
        self._button_group_1.addButton(self._splitter_selector_button)
        self._button_group_1.addButton(self._line_selector_button)

        self._layout.addWidget(self._splitter_selector_button)
        self._layout.addWidget(self._line_selector_button)

        self._label_splitter = self._generate_block_label("Границы отсекателя:")
        self._layout.addWidget(self._label_splitter)

        self._first_xy_co_ords = InputTwoParams(self, name_1="X левый", name_2="Y верхний")
        self._layout.addWidget(self._first_xy_co_ords)

        self._second_xy_co_ords = InputTwoParams(self, name_1="X правый", name_2="Y нижний")
        self._layout.addWidget(self._second_xy_co_ords)

        self._draw_splitter_button = QPushButton("Нарисовать отскатель")
        self._draw_splitter_button.clicked.connect(self._draw_splitter)
        self._layout.addWidget(self._draw_splitter_button)

        self._dot_co_ords = InputTwoParams(self, "Координаты точки: ")
        self._layout.addWidget(self._dot_co_ords)
        self._add_point_button = QPushButton("Добавить новую точку")
        self._add_point_button.clicked.connect(self._add_point)
        self._layout.addWidget(self._add_point_button)

        self._fill_button = QPushButton("Выполнить отсечение")
        self._fill_button.clicked.connect(self._cut)
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

    def _draw_splitter(self):
        first = self._first_xy_co_ords.get_data()

        if first == None:
            return MessageDisplay(self, "Некорректно указаны или отсуствуют данные о левой верхней вершине отсекателя.")

        second = self._second_xy_co_ords.get_data()

        if second == None:
            return MessageDisplay(self, "Некорректно указаны или отсуствуют данные о правой нижней вершине отсекателя.")

        self._draw_splitter_action(first, second)

    def _cut(self):
        self._cut_action()
