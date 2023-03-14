import numpy as np
from NewtonInterpolation import NewtonInterpolation


class SplineInterpolation:
    def __init__(self, array_of_conditions: np.ndarray, newton_start_condition=True, newton_end_condition=True):
        self.data = np.array([], float)
        self._start = 0
        self._end = 0

        self._data_parsing_for_research(array_of_conditions, newton_start_condition, newton_end_condition)
        self.system = np.zeros((len(self.data), 4))
        self._calc_running_coefficients()
        self._calc_system_coefficients_by_running_coefficients()

    def _data_parsing_for_research(self, data: np.ndarray, newton_start_condition, newton_end_condition):
        self.data = data[data[:, 0].argsort(-1)]

        if newton_start_condition:
            first_newton_interpolation = NewtonInterpolation(self.data, self.data[0, 0], 3)
            self._start = first_newton_interpolation.get_second_derivative_result()

        if newton_end_condition:
            second_newton_interpolation = NewtonInterpolation(self.data, self.data[-1, 0], 3)
            self._end = second_newton_interpolation.get_second_derivative_result()

    def get_result_by_value(self, value: float):
        i = np.where(self.data[:, 0] > value)

        position = i[0][0] - 1 if len(i[0]) else len(self.system) - 1

        h_value = value - self.data[position][0]

        return (self.system[position][0] + self.system[position][1] * h_value +
                self.system[position][2] * (h_value ** 2) +
                self.system[position][3] * (h_value ** 3))

    def _calc_running_coefficients(self):
        length = len(self.data)
        self.system[0, 2] = self._start
        self.system[1, 2] = self._end

        self._xee = np.zeros(len(self.data))
        self._etha = np.zeros(len(self.data))

        self._xee[0] = self._start
        self._xee[1] = self._end
        self._etha[0] = self._start
        self._etha[1] = self._end

        for i in range(2, length):
            hi = self.data[i, 0] - self.data[i - 1, 0]
            hi_1 = self.data[i - 1, 0] - self.data[i - 2, 0]

            ai = hi_1
            bi = 2 * (hi_1 + hi)
            di = hi
            fi = 3 * ((self.data[i, 1] - self.data[i - 1, 1]) / di -
                      (self.data[i - 1, 1] - self.data[i - 2, 1]) / ai)

            self._xee[i] = - ai / (di * self._xee[i - 1] + bi)
            self._etha[i] = (fi - ai * self._etha[i - 1]) / (ai * self._xee[i - 1] + bi)

        print()

    def _calc_system_coefficients_by_running_coefficients(self):

        self.system[-1, 2] = self._etha[-1]

        for i in range(len(self.system) - 1, 0, -1):
            self.system[i - 1, 2] = self._xee[i] * self.system[i, 2] + self._etha[i]

        for i in range(0, len(self.system) - 1):
            self.system[i, 0] = self.data[i, 1]

            h = self.data[i + 1, 0] - self.data[i, 0]

            self.system[i, 1] = (self.data[i + 1, 1] - self.data[i, 1]) / h - h * (
                            self.system[i + 1, 2] + 2 * self.system[i, 2]) / 3.0
            self.system[i, 3] = (self.system[i + 1, 2] - self.system[i, 2]) / h / 3.0

        self.system[-1, 0] = self.data[-1, 1]
        h = self.data[-1, 0] - self.data[-2, 0]
        self.system[-1, 1] = (self.data[-1, 1] - self.data[-2, 1]) / h - h * (self._end + 2 * self.system[-1, 2]) / 3.0
        self.system[-1, 3] = (self._end - self.system[-1, 2]) / 3 / h


# df = pd.read_csv("./data/data_2.csv", dtype=float)
# data = df.to_numpy()
# print(SplineInterpolation(data).get_result_by_value(4))
# print(NewtonInterpolation(data, 4, 3).get_interpolation_result())

