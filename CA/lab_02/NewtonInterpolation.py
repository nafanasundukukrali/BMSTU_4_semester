import numpy
import pandas as pd
import numpy as np


class NewtonInterpolation:

    def __init__(self, data: numpy.ndarray, value: float, power):
        self.coefficients = np.array([], float)
        self._value = value
        self._n = power + 1

        self._data = self._prepare_newton_data(data)
        self._get_interpolation_coefficients()

    def _prepare_newton_data(self, data: numpy.ndarray) -> list[list[float]]:
        buffer_n = self._n
        self.data = data[data[:, 0].argsort(-1)]

        closest_to_x0_i = (sorted(range(len(self.data)), key=lambda i: abs(self.data[i][0] - self._value)))[0]

        from_i = closest_to_x0_i - self._n // 2
        if from_i < 0:
            from_i = 0

        to_i = from_i + self._n
        if to_i > len(self.data):
            to_i = len(self.data)
            from_i = to_i - self._n

        self._n = buffer_n

        return self.data[from_i:to_i]

    def _get_interpolation_coefficients(self):
        self.coefficients = self._data[:, 1]

        step = 1

        while step < self._n:
            last_result = self.coefficients[step - 1]

            for i in range(step, self._n):
                pre_last_result = self.coefficients[i]

                self.coefficients[i] = ((self.coefficients[i] - last_result) / (self._data[i][0] -
                                                                                self._data[i - step][0]))

                last_result = pre_last_result

            step += 1

    def get_interpolation_result(self) -> float:
        result = self.coefficients[0]
        tmpCoefficient = 1

        for i in range(1, self._n):
            tmpCoefficient *= self._value - self._data[i - 1][0]
            result += tmpCoefficient * self.coefficients[i]

        return result

    def get_second_derivative_result(self) -> float | None:
        if self._n != 4:
            return None

        result = (2 * self.coefficients[2] + 6 * self.coefficients[3] * (self._value - self.data[3][0]))

        return result



