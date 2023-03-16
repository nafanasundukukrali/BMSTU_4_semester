from SplineInterpolation import SplineInterpolation
from NewtonInterpolation import NewtonInterpolation
import pandas as pd
from decimal import Decimal
from matplotlib import pyplot as plt
import numpy as np

path = input("Введите путь до файла со входными данными: ")
value = input("Введите значение аргумента, для которого выполняется интерполяция: ")

try:
    value = float(value)
except:
    print("Значение аргумента введено некорректно.")
    exit(1)

try:
    df = pd.read_csv(path, dtype=float)
    data = df.to_numpy()
except:
    print("Некорректно введён путь до файла.")
    exit(1)

if len(data) <= 3:
    print("Нехватает данных для апроксимации Ньютоном, необходимо 4 условия.")
    exit(1)

newtonValue = NewtonInterpolation(data, value, 3).get_interpolation_result()

spline_1 = SplineInterpolation(data, newton_start_condition=False,
                               newton_end_condition=False)
spline_2 = SplineInterpolation(data, newton_end_condition=False)
spline_3 = SplineInterpolation(data)

print("=== Интерполяция ===")
print("Значение интерполяции Ньютона: ", "%.6E" % Decimal(newtonValue))
print("Значение сплайн-интерполяции, естественные краевые условия: ", "%.6E" % Decimal(spline_1.get_result_by_value(
    value)))
print("Значение сплайн-интерполяции, на одной границе при x = x0 вторая производная сплайна равна второй производ"
      "ной полинома Ньютона третьей степени: ", "%.6E" % Decimal(spline_2.get_result_by_value(value)))
print("Значение сплайн-интерполяции, на обеих границах при x = x0 и x = xN вторая производная сплайна равна второй "
      "производной полинома Ньютона третьей степени: ", "%.6E" % Decimal(spline_3.get_result_by_value(value)))
print("=== Сравнение результатов интерполяции ===")
print("Ньютон/Естественные краевые условия: ", "%.3E" % Decimal(newtonValue / spline_1.get_result_by_value(
    value)))
print("Ньютон/На одной из границ производная: ", "%.3E" % Decimal(newtonValue / spline_2.get_result_by_value(
    value)))
print("Ньютон/На обеих границах производные: ", "%.3E" % Decimal(newtonValue / spline_3.get_result_by_value(
    value)))

data = data[data[:, 0].argsort(-1)]
x_spline = np.arange(data[0][0], data[-1][0], 0.01)
y_spline_1 = np.zeros(x_spline.size)
y_spline_2 = np.zeros(x_spline.size)
y_spline_3 = np.zeros(x_spline.size)
y_newton = np.zeros(x_spline.size)
# newton = NewtonInterpolation(data, x_spline[x_spline.size // 2], 3)

for i in range(x_spline.size):
    y_spline_1[i] = spline_1.get_result_by_value(x_spline[i])
    y_spline_2[i] = spline_2.get_result_by_value(x_spline[i])
    y_spline_3[i] = spline_3.get_result_by_value(x_spline[i])
    # y_newton[i] = newton.get_interpolation_result_2(x_spline[i])
    y_newton[i] = NewtonInterpolation(data, x_spline[i], 3).get_interpolation_result()

plt.plot(data[:, 0], data[:, 1], 'o')
plt.plot(x_spline, y_newton)
plt.plot(x_spline, y_spline_1)
plt.plot(x_spline, y_spline_2)
plt.plot(x_spline, y_spline_3)
plt.legend(['Входные данные',
            'Апроксимация с использованием полинома Ньютона',
            'Апроксимация с использованием сплайн-интерполяции, естественные краевые условия',
            "Апроксимация с использованием сплайн-интерполяции, на одной границе при x = x0 вторая производная "
            "сплайна равна второй производ"
            "ной полинома Ньютона третьей степени",
            "Апроксимация с использованием сплайн-интерполяции, на обеих границах при x = x0 и x = xN вторая "
            "производная сплайна равна второй производной полинома Ньютона"
            "третьей степени: "], loc="upper center", bbox_to_anchor=(0.5, 1.15))

figmgr = plt.get_current_fig_manager()
bkend = plt.get_backend()

if bkend == 'TkAgg':
    figmgr.resize(*figmgr.window.maxsize())

plt.show()
