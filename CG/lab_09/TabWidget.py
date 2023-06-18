from PySide6.QtWidgets import QWidget, QVBoxLayout, QTabWidget, QLabel, QHBoxLayout
from OneInputField import OneInputField


class TabWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.layout = QVBoxLayout()

        # Initialize tab screen
        self.tabs = QTabWidget()
        self.tab1 = QWidget()
        self.tab2 = QWidget()
        self.tab3 = QWidget()

        self.tabs.addTab(self.tab1, "Окружность")
        self.tabs.addTab(self.tab2, "Эллипс")

        self.tab1.layout = QVBoxLayout(self)
        # self.setMinimumHeight(100)
        # self.tabs.setMinimumHeight(100)
        self._circle_radius_spec = OneInputField(self, "Радиус окружности")
        self.tab1.layout.addWidget(self._circle_radius_spec)
        self.tab1.setLayout(self.tab1.layout)

        self.layout.addWidget(self.tabs)
        self.setLayout(self.layout)

        h_2 = QVBoxLayout()

        self._ellipse_a_spec = OneInputField(self, "Большая полуось")

        self._ellipse_b_spec = OneInputField(self, "Малая полуось")
        # self._ellipse_b_spec.setMinimumHeight(5)
        # self._ellipse_a_spec.setMinimumHeight(5)

        h_2.addWidget(self._ellipse_a_spec)
        h_2.addWidget(self._ellipse_b_spec)

        self.tab2.setLayout(h_2)

    def get_data(self):
        if self.tabs.currentIndex() == 0:
            data = self._circle_radius_spec.get_data()

            if not data:
                return [0]
            else:
                return [0, data]
        else:
            data_1 = self._ellipse_a_spec.get_data()
            data_2 = self._ellipse_b_spec.get_data()

            if not data_1 or not data_2:
                return [1]
            else:
                return [1, data_1, data_2]