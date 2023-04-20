from PySide6.QtWidgets import QDialog, QVBoxLayout
from PySide6.QtCore import Qt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Figure

class TimePlot(QDialog):
    def __init__(self, parent, results_circle, results_ellipse, step, step_count, start_a, start_b):
        super().__init__(parent)
        self.setFixedWidth(int(parent.width() * 2.7))
        self.setFixedHeight(parent.height())
        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)
        self.toolbar = NavigationToolbar(self.canvas, self)
        layout = QVBoxLayout()
        layout.addWidget(self.toolbar)
        layout.addWidget(self.canvas)
        self.setLayout(layout)
        self.plot(results_circle, results_ellipse, step, step_count, start_a, start_b)
        self.showMaximized()

    def plot(self, results_circle, results_ellipse, step, step_count, start_a, start_b):
        def chng_data():
            buffer = results_ellipse["Параметрическое\nуравнение"]
            results_ellipse["Параметрическое\nуравнение"] = results_ellipse["Метод\nсредней\nточки"]
            results_ellipse["Метод\nсредней\nточки"] = buffer

            buffer = results_ellipse["Метод\nсредней\nточки"]
            results_ellipse["Метод\nсредней\nточки"] = results_ellipse["Каноническое\nуравнение"]
            results_ellipse["Каноническое\nуравнение"] = buffer

        x = [i for i in range(start_b, step_count * step + start_b, step)]
        ax_1 = self.figure.add_subplot(121)
        ax_1.clear()
        ax_1.set_title(f'Исследование временных характеристик построения окружности \n (начальный радиус = {start_a}, '
                       f'шаг изменения радиуса = {step},\n количество фигур = {step_count})')
        ax_1.set_xlabel("Радиус окружности")
        ax_1.set_ylabel("Время (ns)")

        for key in results_circle.keys():
            ax_1.plot(x, results_circle[key], label=key)

        chng_data()

        ax_2 = self.figure.add_subplot(122)
        ax_2.clear()
        ax_2.set_title(f'Исследование временных характеристик построения эллипса \n'
                       f'(начальная длина большей полуоси = {start_a}, шаг изменения длины полуоси = {step},\n'
                       f' количество фигур = {step_count})')
        ax_2.set_xlabel("Длина большей полуоси")
        ax_2.set_ylabel("Время (ns)")
        for key in results_ellipse.keys():
            ax_2.plot(x, results_ellipse[key], label=key)

        ax_1.legend()
        ax_2.legend()

        self.canvas.draw()
