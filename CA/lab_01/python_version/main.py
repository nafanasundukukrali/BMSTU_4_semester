from math import factorial
import pandas as pd
import numpy as np

def getInterpolationCoefficients(preparedData: list[list[float]]) -> list[float]:
    result = [preparedData[_][1] for _ in range(len(preparedData))]

    step = 1

    while step < len(preparedData):
        last_result = result[step-1];

        for i in range (step, len(preparedData)):
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
    result = []
    
    position = searchApproximationPosition(data, value)
    right = position
    left = position + 1
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
    position = searchApproximationPosition(data, value)
    right = position
    left = position + 1

    while n > 0:
        if right >= 0:
            right -= 1
            n -= 1
        if left < len(data) and n > 0:
            left += 1
            n -= 1
    
    if right < 0:
        right += 1

    return data[right:left]
    

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

    for i in range(1, n + 1):
        tmpCoefficient *= value - data[i - 1][0]
        result += tmpCoefficient * coefficients[i]

    return result

def getNewtonIntepolation(data: list[list[float]],
                          value: float,
                          n: int) -> float:

    tmpData = prepareNewtonData(data, value, power)
    coefficients = getInterpolationCoefficients(tmpData)
    
    return getInterpolationResult(coefficients, tmpData, value, n)

def getHermiteInterpolation(data: list[list[float]],
                            value: float,
                            n: int) -> float:
    data2 = prepareHermiteData(data, value, n)
    newcoefficients = getInterpolationCoefficients(data2)

    return getInterpolationResult(newcoefficients, data2, value, n)

testData_1 = [
        [-0.5, 0.707],
        [-0.25, 0.924],
        [0.0, 1.0],
        [0.25, 0.924],
        [0.50, 0.707],
        [0.75, 0.383],
        [1.0, 0],
        ]

testData_2 = [
        [0.0, 1.0, -1.0],
        [0.15, 0.838771, -1.14944],
        [0.30, 0.655336, -1.29552],
        [0.45, 0.450447, -1.43497],
        [0.60, 0.225336, -1.56464],
        [0.75, -0.018310, -1.168164],
        [0.90, -0.278390, -1.78333],
        [1.05, -0.552430, -1.86742]
        ]

value = float(input("Введите аргумент, для которого выполняется интерполяция: "))
power = int(input("Введите степень аппроксимирующих полиномов: "))
dataPath = input("Введите путь до файла с тестовыми данными: ")
print()

df = pd.read_csv(dataPath, dtype=float)
data = df.to_numpy().tolist()

print(f'Фиксированное x: {value}')


newtonData = [ getNewtonIntepolation(data, value, i) for i in range(1, power +
                                                                    1) ]
hermitedata = [ getHermiteInterpolation(data, value, i) for i in range(1, power
                                                                       + 1) ]

print("Таблица значений y(x) при степенях полиномов Ньютона и Эрмита n= 1, 2, 3, 4 и 5 при фиксированном x")

df2 = pd.DataFrame( 
                   {
                       "Степень": [ i for i in range(1, 6) ],
                        "Ньютона" : newtonData,
                        "Эрмита" : hermitedata
                     }
                   )

print(df2)

'''
print("Newton")
data = prepareNewtonData(testData_2, value, power)
print(data)
coefficients = getInterpolationCoefficients(data)
print(coefficients)
print(getInterpolationResult(coefficients, data, value, power))
print("Hermite")
data2 = prepareHermiteData(testData_2, value, power)
print(data)
newcoefficients = getInterpolationCoefficients(data)
print(newcoefficients)
print(getInterpolationResult(newcoefficients, data2, value, power))
'''
