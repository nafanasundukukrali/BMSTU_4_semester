from PySide6.QtWidgets import (QWidget, QPushButton, QVBoxLayout, QHBoxLayout, QLabel, QFrame, QRadioButton)
from PySide6.QtGui import QFont, Qt
from PySide6.QtCore import QPoint

from AlgorithmFunctions import AlgorithmFunctions
from config import MessageDisplay, TASK
from OneInputField import OneInputField
from AlgorithmSelectionField import AlgorithmSelectionField
from ColorSelectionField import ColorSelectionField
from InputTwoParams import InputTwoParams
import statistics

from TimePlot import TimePlot
from StepsPlot import StepsPlot
from SpaceAndCountSelection import SpaceAndCountSelection
from TabWidget import TabWidget


class ControlField(QWidget):
    MINWIDTH = 450
    cords_text = "Координаты центра: "
    cords_zero_status = "Пока не определены"
    start_of_last_action_status = "Отмена последнего преобразования"

    def __init__(self, parent, draw_circle_or_ellipse_action, draw_spec_action, clean_action):
        super().__init__(parent)
        self._draw_circle_or_ellipse_action = draw_circle_or_ellipse_action
        self._draw_spec_action = draw_spec_action
        self._parent = parent
        self.setMinimumWidth(self.MINWIDTH)
        self._layout = QVBoxLayout()

        self._algorithm_selection = AlgorithmSelectionField(self)
        self.setLayout(self._layout)
        self._layout.addWidget(self._algorithm_selection)

        h_l = QHBoxLayout()
        self._backgroud_color_widget = ColorSelectionField(self, "  Выбрать цвет фона  ", self.width())

        self._pen_color_widget = ColorSelectionField(self, "  Выбрать цвет линии  ", self.width())
        h_l.addWidget(self._backgroud_color_widget)
        h_l.addWidget(self._pen_color_widget)
        self._layout.addLayout(h_l)

        self._label_circle = self._generate_block_label("Нарисовать окружность:")
        self._layout.addWidget(self._label_circle)

        self._circle_center = InputTwoParams(self, "Координаты центра: ")
        self._layout.addWidget(self._circle_center)

        self._circle_radius = OneInputField(self, "Радиус окружности")
        self._layout.addWidget(self._circle_radius)

        self._draw_circle_button = QPushButton("Нарисовать окружность")
        self._draw_circle_button.clicked.connect(self._draw_circle)
        self._layout.addWidget(self._draw_circle_button)

        self._label_circle = self._generate_block_label("Нарисовать эллипс:")
        self._layout.addWidget(self._label_circle)

        self._ellipse_center = InputTwoParams(self, "Координаты центра: ")
        self._layout.addWidget(self._ellipse_center)

        self._ellipse_data = InputTwoParams(self, name_1="Большая полуось", name_2="Малая полуось")
        self._layout.addWidget(self._ellipse_data)

        self._draw_ellipse_button = QPushButton("Нарисовать Эллипс")
        self._draw_ellipse_button.clicked.connect(self._draw_ellipse)
        self._layout.addWidget(self._draw_ellipse_button)

        self._label_circle = self._generate_block_label("Нарисовать спектр:")
        self._layout.addWidget(self._label_circle)

        self._tabs = TabWidget()
        self._layout.addWidget(self._tabs)
        self._layout.stretch(0)

        self._spec_params = InputTwoParams(self, name_1="Шаг спектра", name_2="Количесто фигур", type_data=int)
        self._layout.addWidget(self._spec_params)

        self._draw_spec_button = QPushButton("Нарисовать спектр")
        self._draw_spec_button.clicked.connect(self._draw_spec)
        self._layout.addWidget(self._draw_spec_button)

        self._label_circle = self._generate_block_label("Исследование характеристик алгоритмов:")
        self._layout.addWidget(self._label_circle)

        self._time_analyz = QPushButton("Исследование времени работы")
        self._time_analyz.clicked.connect(self._time_analyze)
        self._layout.addWidget(self._time_analyz)

        self._clear = QPushButton("Очистить экран")
        self._clear.clicked.connect(clean_action)

        # self._task = QPushButton("Задание")
        # self._task.clicked.connect(self._print_task)

        self._layout.addWidget(self._clear)
        # self._layout.addWidget(self._task)

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

    def _draw_circle(self):
        algorithm = self._algorithm_selection.get_selected_algorithm_type()
        pen_color = self._pen_color_widget.get_color()
        background_color = self._backgroud_color_widget.get_color()

        center = self._circle_center.get_data()

        if center == None:
            return MessageDisplay(self, "Некорректно указаны или отсуствуют данные о центре окружности.")

        radius = self._circle_radius.get_data()

        if radius == None:
            return MessageDisplay(self, "Некорректно указаны или отсуствуют данные о радиусе окружности.")

        self._draw_circle_or_ellipse_action(algorithm, center, radius, radius,
                                            pen_color, background_color, is_circle=True)

    def _draw_ellipse(self):
        algorithm = self._algorithm_selection.get_selected_algorithm_type()
        pen_color = self._pen_color_widget.get_color()
        background_color = self._backgroud_color_widget.get_color()

        center = self._ellipse_center.get_data()

        if center == None:
            return MessageDisplay(self, "Некорректно указаны или отсуствуют данные о центре эллипса.")

        data = self._ellipse_data.get_data()

        if data == None:
            return MessageDisplay(self, "Некорректно указаны или отсуствуют данные о полуосях эллипса.")

        self._draw_circle_or_ellipse_action(algorithm, center, *(data.toTuple()), pen_color, background_color)

    def _draw_spec(self):
        algorithm = self._algorithm_selection.get_selected_algorithm_type()
        pen_color = self._pen_color_widget.get_color()
        background_color = self._backgroud_color_widget.get_color()

        data = self._tabs.get_data()

        if len(data) == 1:
            return MessageDisplay(self, f'Некорректно указаны или '
                                        f'отсуствуют данные {"окружности" if data[0] == 0 else "эллипса"} для '
                                        f'построения спектра.')

        spec_params = self._spec_params.get_data()

        if not spec_params:
            return MessageDisplay(self, "Некорректно указаны шаг изменения или количество фигур.")

        if data[0] == 0:
            self._draw_spec_action(algorithm, *(spec_params.toTuple()), data[1], data[1], pen_color=pen_color,
                                   background_color=background_color, is_circle=True)
        else:
            self._draw_spec_action(algorithm, *(spec_params.toTuple()), data[1], data[2], pen_color=pen_color,
                                   background_color=background_color)

    def _time_analyze(self):
        results_circle = {}
        results_ellipse = {}
        all_algorithms = AlgorithmFunctions().get_algorithms_list()
        count = 10
        step_count = 10
        start_a = 100
        start_b = 50
        step = 100

        self._draw_circle_or_ellipse_action(all_algorithms['Алгоритм Брезенхема'], QPoint(0, 0),
                                            start_a + step, start_a + step,
                                            is_circle=True, time_analyze=True)

        for algorithm in all_algorithms.keys():
            values = []
            for i in range(step_count):
                buffer = []

                for j in range(count):
                    buffer.append(self._draw_circle_or_ellipse_action(all_algorithms[algorithm], QPoint(0, 0),
                                                                      start_a + step * i, start_a + step * i,
                                                                      is_circle=True, time_analyze=True))

                values.append(statistics.median_low(buffer))

            results_circle['\n'.join(algorithm.split())] = values

        for algorithm in all_algorithms.keys():
            values = []
            for i in range(step_count):
                buffer = []

                for j in range(count):
                    buffer.append(self._draw_circle_or_ellipse_action(all_algorithms[algorithm], QPoint(0, 0),
                                                                      start_a + step * i,
                                                                      start_a + step * i, time_analyze=True))

                values.append(statistics.median_low(buffer))

            results_ellipse['\n'.join(algorithm.split())] = values

        TimePlot(self, results_circle, results_ellipse, step, step_count, start_a, start_b)
