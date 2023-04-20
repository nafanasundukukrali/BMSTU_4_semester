import numpy as np


class NewtonInterpolation:

    def __init__(self, data: np.ndarray, value: float, power):
        self.coefficients = np.array([], float)
        self._value = value
        self._n = power + 1

        self._data = self._prepare_newton_data(data)
        self._get_interpolation_coefficients()

    @staticmethod
    def findCoefIndex(line, coef):
        index = 0
        for i in range(len(line)):
            if abs(line[i] - coef) < abs(line[index] - coef):
                index = i
        return index

    def _prepare_newton_data(self, data: np.ndarray) -> list[list[float]]:
        data = data[data[:, 0].argsort(-1)]
        index = self.findCoefIndex(data[:, 0], self._value)

        left = index
        right = index

        for i in range(self._n - 1):
            if i % 2 != 0:
                if left == 0:
                    right += 1
                else:
                    left -= 1
            else:
                if right == len(data[:, 0]) - 1:
                    left -= 1
                else:
                    right += 1

        return data[left:right + 1]
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


