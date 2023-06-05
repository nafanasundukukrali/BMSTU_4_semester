from math import fabs, pi, exp
import matplotlib.pyplot as plt
def solve_ls_by_gaus_method(matrix):
    n = len(matrix)

    for i in range(n):
        maxEl = abs(matrix[i][i])
        maxRow = i

        for k in range(i + 1, n):
            if abs(matrix[k][i]) > maxEl:
                maxEl = abs(matrix[k][i])
                maxRow = k

        for k in range(i, n + 1):
            tmp = matrix[maxRow][k]
            matrix[maxRow][k] = matrix[i][k]
            matrix[i][k] = tmp

        for k in range(i + 1, n):
            c = - matrix[k][i] / matrix[i][i]
            for j in range(i, n + 1):
                if i == j:
                    matrix[k][j] = 0
                else:
                    matrix[k][j] += c * matrix[i][j]

    result = [0.0 for _ in range(n)]

    for i in range(n - 1, -1, -1):
        result[i] = matrix[i][-1]

        for j in range(i + 1, n):
            result[i] -= matrix[i][j] * result[j]

        result[i] /= matrix[i][i]

    return result

def task_1(epsilon: float):
    X0 = [0.5, 0.5, 0.5]

    F = [lambda x, y, z: x ** 2 + y ** 2 + z ** 2 - 1,
         lambda x, y, z: 2 * x ** 2 + y ** 2 - 4 * z,
         lambda x, y, z: 3 * x ** 2 - 4 * y + z ** 2,
         ]

    J = [[lambda x: 2 * x, lambda y: 2 * y, lambda z: 2 * z],
         [lambda x: 4 * x, lambda y: 2 * y, lambda z: -4],
         [lambda x: 6 * x, lambda y: -4, lambda z: 2 * z]
         ]

    delx0 = 0.0; dely0 = 0.0; delz0 = 0.0
    start = True

    while start or max(fabs(delx0), fabs(dely0), fabs(delz0)) >= epsilon:
        actual_J = [[J[i][j](X0[j]) for j in range(3)] for i in range(3)]

        for i in range(3):
            actual_J[i].append(-F[i](*X0))

        delx0, dely0, delz0 = solve_ls_by_gaus_method(actual_J)

        X0 = [ X0[0] + delx0, X0[1] + dely0, X0[2] + delz0 ]

        start = False

    return X0

def task_2(value, epsilon):
    N = 17

    def simpson(y):
        f = lambda x: 1 / ((2 * pi) ** 0.5) * exp(-(x ** 2) / 2)

        h = y / (N * 2)

        X0 = [i * h for i in range(N * 2 + 1)]
        f_v = [f(x_i) for x_i in X0]

        sum1 = 4 * sum([f_v[2 * i - 1] for i in range(1, N)])
        sum2 = 2 * sum([f_v[2 * i] for i in range(1, N - 1)])

        return (h / 3) * (f_v[0] + f_v[-1] + sum1 + sum2)


    left = 0
    right = 5

    while (value > simpson(right - left)):
        left = right
        right *= 2

    left = 0
    right = 5

    midX = (right + left) / 2

    while (right - left) / midX > epsilon:
        if (simpson(right) - value) * (simpson(midX) - value) > 0:
            left = right
            right = midX
        else:
            right = left
            left = midX

        midX = (right + left) / 2

    return midX

def task_3(epsilon):
    N = 100

    start = 0
    w = []
    h = 1 / N

    for i in range(N, 0, -1):
        w.append(start)
        start += h

    y = [ 2 * w[i] + 1 for i in range(N)]
    y_orig = y.copy()

    delta = [0 for _ in range(N)]

    start = True

    while start or max(map(fabs, delta)) > epsilon:
        ksi = [0 for i in range(N - 1)]
        et = [0 for i in range(N - 1)]

        for i in range(1, len(ksi)):
            A = 1
            C = 1

            B = A + C + 3 * h ** 2 * y[i]

            F = y[i - 1] - 2 * y[i] + y[i + 1] - \
                h ** 2 * (w[i] ** 2 + y[i] ** 3)

            ksi[i] = C / (B - A * ksi[i - 1])
            et[i] = (A * et[i - 1] + F) / (B - A * ksi[i - 1])

        delta = [0 for i in range(N)]

        for i in range(len(ksi) - 1, 0, -1):
            delta[i] = ksi[i] * delta[i + 1] + et[i]

        for i in range(len(y)):
            y[i] = y[i] + delta[i]

        start = False

    return w, y, y_orig

task = int(input('Введите номер задания: '))
epsilon = float(input('Введите точность: '))

if task == 1:
    X0 = task_1(epsilon)
    print('Результат: ', *X0)
elif task == 2:
    y = float(input('Введите значение функции Лапласа: '))
    value = task_2(y, epsilon)
    print("x: ", value)
else:
    w, y, y_orig = task_3(epsilon)
    plt.grid()
    plt.plot(w, y_orig, label="Init values")
    plt.plot(w, y, label="Result values")
    plt.legend()
    plt.show()
