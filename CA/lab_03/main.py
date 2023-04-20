import numpy as np
from NewtonInterpolation import NewtonInterpolation
from SplineInterpolation import SplineInterpolation


def all_newton_interpolation(data, x, y, z, nx, ny, nz):
    z_interpolation_data = []

    for z_array in data:
        y_interpolation_data = []

        for j in range(len(z_array[1])):
            x_interpolation_data = np.array(z_array[1][j][1], dtype=float)
            newton_polynom = NewtonInterpolation(x_interpolation_data, x, nx)
            y_interpolation_data.append([z_array[1][j][0], newton_polynom.get_interpolation_result()])

        y_interpolation_data = np.array(y_interpolation_data, dtype=float)
        newton_polynom = NewtonInterpolation(y_interpolation_data, y, ny)
        z_interpolation_data.append([z_array[0], newton_polynom.get_interpolation_result()])

    z_interpolation_data = np.array(z_interpolation_data, dtype=float)

    return NewtonInterpolation(z_interpolation_data, z, nz).get_interpolation_result()


def all_spline_interpolation(data, x, y, z, nx, ny, nz):
    z_interpolation_data = []

    for z_array in data:
        y_interpolation_data = []

        for j in range(len(z_array[1])):
            x_interpolation_data = np.array(z_array[1][j][1], dtype=float)
            spline_interpolation = SplineInterpolation(x_interpolation_data)
            y_interpolation_data.append([z_array[1][j][0], spline_interpolation.get_result_by_value(x)])

        y_interpolation_data = np.array(y_interpolation_data, dtype=float)
        spline = SplineInterpolation(y_interpolation_data)
        z_interpolation_data.append([z_array[0], spline.get_result_by_value(y)])

    z_interpolation_data = np.array(z_interpolation_data, dtype=float)

    return SplineInterpolation(z_interpolation_data).get_result_by_value(z)


def all_different_interpolation(data, x, y, z, nx, ny, nz):
    z_interpolation_data = []

    for z_array in data:
        y_interpolation_data = []

        for j in range(len(z_array[1])):
            x_interpolation_data = np.array(z_array[1][j][1], dtype=float)
            newton_interpolation = NewtonInterpolation(x_interpolation_data, x, nx)
            y_interpolation_data.append([z_array[1][j][0], newton_interpolation.get_interpolation_result()])

        y_interpolation_data = np.array(y_interpolation_data, dtype=float)
        spline = SplineInterpolation(y_interpolation_data)
        z_interpolation_data.append([z_array[0], spline.get_result_by_value(y)])

    z_interpolation_data = np.array(z_interpolation_data, dtype=float)

    return NewtonInterpolation(z_interpolation_data, z, nz).get_interpolation_result()


def get_data(filepath: str):
    data = []

    with open(filepath, "r") as file:
        table_lines = [line.strip() for line in file]
        xs = []
        zs = []

        for line in table_lines:
            if line == "":
                data.append(zs)
                zs = []
            elif "z=" in line:
                xs = []
                z = float(line[list(line).index("=") + 1])
                zs.append(z)
                zs.append([])
            elif "y" in line:
                xs = list(map(float, line.split()[1:]))
            else:
                buffer = line.split()
                zs[1].append([float(buffer[0]), []])

                for i in range(len(xs)):
                    zs[1][-1][-1].append([xs[i], float(buffer[i + 1])])

        if zs:
            data.append(zs)

    return data

nx, ny, nz = map(int, input("Введите степени аппроксимирующих полиномов через пробел nx, ny, nz: ").split())
x, y, z = map(float, input("Введите значения через пробел, для которых выполняется интерполяция: ").split())
table = get_data(input("Введит путь до файла: "))

print("Считанная таблица входных значений: ")
print(*table, sep="\n")

print("Результат интерполяции полиномом Ньютона: ")
print('{:.4}'.format(all_newton_interpolation(table, x, y, z, nx, ny, nz), 3))
print("Результат интерполяции сплайном: ")
print('{:.4}'.format(all_spline_interpolation(table, x, y, z, nx, ny, nz), 3))
print("Результат интепроляции сплайном по направлению y и полиномом Ньютона во всех остальных направлениях: ")
print('{:.4}'.format(all_different_interpolation(table, x, y, z, nx, ny, nz), 3))

