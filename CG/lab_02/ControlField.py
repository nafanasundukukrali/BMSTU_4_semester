from PySide6.QtWidgets import (QWidget, QPushButton, QVBoxLayout, QLabel)
from config import MessageDisplay, TASK
from InputWidget import InputField


class ControlField(QWidget):
    MINWIDTH = 400
    cords_text = "Координаты центра: "
    cords_zero_status = "Пока не определены"
    start_of_last_action_status = "Отмена последнего преобразования"

    def __init__(self, update_action, restart_action, figure):
        super().__init__()
        self._update_figure_action = update_action
        self._restart_action = restart_action

        self._figure = figure
        self._layout = QVBoxLayout()
        self._layout.addStretch()
        self._layout.addStretch()

        self._start_button = QPushButton("Вывод исходного изображения", self)
        self._start_button.clicked.connect(self._restart_figure)

        self._center_label = QLabel(self.cords_text + self.cords_zero_status)
        self._center_label.setStyleSheet("margin: 5px; border: 2px dashed white; padding: 5px")

        self._move_input = InputField(self, self._update_figure, 'move')
        self._scale_input = InputField(self, self._update_figure, 'scale')
        self._rotate_input = InputField(self, self._update_figure, 'rotate')

        self._return_action = QPushButton(self.start_of_last_action_status)
        self._return_action.clicked.connect(self._last_action_return)

        self._task_label = QLabel(TASK)
        self._task_label.setWordWrap(True)
        self._task_label.setStyleSheet("margin: 5px; border: 2px dashed white; padding: 5px")

        self._layout.addStretch()
        self._layout.addWidget(self._start_button)
        self._layout.addWidget(self._center_label)
        self._layout.addWidget(self._move_input)
        self._layout.addWidget(self._scale_input)
        self._layout.addWidget(self._rotate_input)
        self._layout.addWidget(self._return_action)
        self._layout.addWidget(self._task_label)
        self._layout.addStretch(10)
        self.setLayout(self._layout)

    def _update_figure(self, widget_type, data):
        if self._figure.check_figure_free_status():
            MessageDisplay(self, "Фигура не была загружена, невозможно выполнить преобразование.")
            return

        if widget_type == 'move':
            if data[0] < 0.5 and data[1] < 0.5:
                MessageDisplay(self, "Смещение меньше 0.5, перенос не будет осуществлен.")
                return

            self._figure.move_figure(*data)
        elif widget_type == 'scale':
            self._figure.scale_figure(*data)
        elif widget_type == 'rotate':
            self._figure.rotate_figure(*data)

        self._change_center_status()
        self._update_figure_action()

    def _restart_figure(self):
        self._restart_action()
        self._change_center_status()

    def _last_action_return(self):
        if self._figure.check_figure_free_status():
            MessageDisplay(self, "Фигура не была загружена, невозможно выполнить преобразование.")
            return

        if not self._figure.check_reverse_figure_ability():
            self._figure.reverse_figure()
            self._change_center_status()
            self._update_figure_action()
        else:
            MessageDisplay(self, "Фигура или вернулась к предыдущему преобразованию, "
                                 "или не было выполнено ни одного её преобразования.")

    def _change_center_status(self):
        center = self._figure.get_center_cords()
        self._center_label.setText(self.cords_text + f'({center[0]:.1f}; {center[1]:.1f})')