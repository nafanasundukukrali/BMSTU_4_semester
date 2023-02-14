from math import factorial
import pandas as pd
import numpy as np

def getInterpolationCoefficients(preparedData: list[list[float]], n) -> list[float]:
    result = [preparedData[_][1] for _ in range(n)]

    step = 1

    while step < n:
        last_result = result[step-1];

        for i in range (step, n):
            pre_last_result = result[i];

            if preparedData[i - step][0] == preparedData[i][0]:
                result[i] = preparedData[i][step + 1] / factorial(step)
            else:
                result[i] = ((result[i] - last_result) /
                (preparedData[i][0] - preparedData[i - step][0]))

            last_result = pre_last_result
        
        step += 1


    return result


def prepareHermiteData(data: list[list[float]], value: float, n: int) -> list[list[float]]:
    data.sort(key=lambda x: x[0]) 
    result = []
    
    
    position = searchApproximationPosition(data, value)
    
    if position == len(data):
        right = position - 1
    else:
        right = position

    left = right + 1
    n += 1

    while n > 0:
        if right >= 0:
            count = 0

            while count < len(data[right][1:]) and count < n:
                result.insert(0, data[right])
                count += 1

            n -= len(data[right][1:])
            right -= count

        if left < len(data) and n > 0:
            count = 0

            while count < len(data[left][1:]) and count < n:
                result.append(data[left])
                count += 1

            n -= len(data[left][1:])
            left += count

    if right < 0:
        right += 1

    return result

def prepareNewtonData(data: list[list[float]], value: float, n: int) -> list[list[float]]:
    data.sort(key=lambda x: x[0]) 
    position = searchApproximationPosition(data, value)
    right = position
    left = position + 1

    while n >= 0:
        if right >= 0:
            right -= 1
            n -= 1
        if left < len(data) and n >= 0:
            left += 1
            n -= 1
    
    right += 1

    return data[right:left-1]
    

def searchApproximationPosition(data: list[list[float]], value: float) -> int:
    result = 0

    while result < len(data) and data[result][0] < value:
        result += 1

    return result


def getInterpolationResult(coefficients: list[float], 
                           data: list[list[float]],
                           value: float, 
                           n: int) -> float:
    result = coefficients[0]
    tmpCoefficient = 1

    for i in range(1, n):
        tmpCoefficient *= value - data[i - 1][0]
        result += tmpCoefficient * coefficients[i]

    return result

def getNewtonIntepolation(data: list[list[float]],
                          value: float,
                          n: int) -> float:

    tmpData = prepareNewtonData(data, value, n + 1)
    coefficients = getInterpolationCoefficients(tmpData, n + 1)
    
    return getInterpolationResult(coefficients, tmpData, value, n + 1)

def getHermiteInterpolation(data: list[list[float]],
                            value: float,
                            n: int) -> float:
    data2 = prepareHermiteData(data, value, n + 1)
    newcoefficients = getInterpolationCoefficients(data2, n + 1)

    return getInterpolationResult(newcoefficients, data2, value, n + 1)

def getReverseIntepolationValue(data: list[list[float]], 
                                value: float, 
                                n: int) -> list[float]:
    newData = swapColumnsXY(data)
    xNewton = getNewtonIntepolation(newData, value, n)
    xHermite = getHermiteInterpolation(newData, value, n)

    return [xNewton, xHermite] 

def swapColumnsXY(data):
     # newDatadf1 = [[data[i][1], data[i][0]] for i in range(len(data))]
    newDatadf1 = []

    for i in range(len(data)):
        newDatadf1.append([data[i][1], data[i][0]])
    
        for j in range(2, len(data[i])):
            newDatadf1[i].append(1/data[i][j])

    newDatadf1.sort(key=lambda x: x[0])

    return newDatadf1

value = float(input("Введите аргумент, для которого выполняется интерполяция: "))
power = int(input("Введите степень аппроксимирующих полиномов: "))
dataPath = input("Введите путь до файла с тестовыми данными: ")
print()
print("=== Задание 1 ===")

df = pd.read_csv(dataPath, dtype=float)
data = df.to_numpy().tolist()

print(f'Фиксированное x: {value}')


newtonData = [ getNewtonIntepolation(data, value, i) for i in range(1, power +
                                                                    1) ]
hermitedata = [ getHermiteInterpolation(data, value, i) for i in range(1, power
                                                                       + 1) ]

print("Таблица значений y(x) при указанных степенях полиномов: ")

df2 = pd.DataFrame( 
                   {
                       "Степень": [ i for i in range(1, power + 1) ],
                        "Полином Ньютона" : map('{:,.3f}'.format, newtonData),
                        "Полином Эрмита" : map("{:,.3f}".format, hermitedata)
                        }
                   )

print(df2.to_string(index=False))
print()
print("=== Задание 2 ===")
print("Обратная интерполяция:")

resultReverse = getReverseIntepolationValue(data, 0, power)

print(f'Значение с использованием полинома Ньютона: {"{:,.3f}".format(resultReverse[0])} \n'
      f'Значение с использованием полинома Эрмита: {"{:,.3f}".format(resultReverse[1])}')

print()
print("=== Задание 3 ===") 

power = int(input("Введите степень аппроксимирующих полиномов: "))
path_1 = input("Введите путь до первой таблицы: ")
path_2 = input("Введите путь до второй таблицы: ")

df1 = pd.read_csv(path_1, dtype=float)
data1 = df1.to_numpy().tolist()

df2 = pd.read_csv(path_2, dtype=float)
data2 = df2.to_numpy().tolist()

newYColumnData = []

for i in range(len(data2)):
    newYColumnData.append(getReverseIntepolationValue(data1, data2[i][0],
                                                       power)[0])

for i in range(len(newYColumnData)):
    data2[i].insert(0, newYColumnData[i] - data2[i][1])
    data2[i].pop(2)

resultx = getNewtonIntepolation(data2, 0.0, power)
resulty = getReverseIntepolationValue(data1, resultx, power)

print(f'Искомое значение: x={"{:,.3f}".format(resultx)}, y={"{:,.3f}".format(resulty[1])}')
