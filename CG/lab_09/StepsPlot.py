from PySide6.QtWidgets import QDialog, QVBoxLayout
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Figure

class StepsPlot(QDialog):
    def __init__(self, parent, data, step_count, angle):
        super().__init__(parent)
        self.setFixedWidth(int(parent.width() * 2.5))
        self.setFixedHeight(parent.height())
        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)
        self.toolbar = NavigationToolbar(self.canvas, self)
        layout = QVBoxLayout()
        layout.addWidget(self.toolbar)
        layout.addWidget(self.canvas)
        self.setLayout(layout)

        self.plot(data, step_count, angle)

        self.canvas.draw()
        self.show()

    def plot(self, data, step_count, angle):
        linestyle_tuple = ['-r', '-g', ':k', ':b', '-y', ':']

        ax = self.figure.add_subplot(111)
        ax.clear()
        ax.set_title(f'Исследование ступенчатости (длина отрезка = {step_count}, угол = {angle})')
        ax.set_xlabel("Угол (в градусах)")
        ax.set_ylabel("Количество ступенек")
        values = [i for i in range(0, 91, 5)]

        i = 0
        for algorithm in data.keys():
            ax.plot(values, data[algorithm], linestyle_tuple[i],linewidth=2,  label=algorithm)
            i += 1

        ax.legend()
        ax.set_xticks(values)