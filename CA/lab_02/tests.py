from SplineInterpolation import SplineInterpolation
import pandas as pd
from decimal import Decimal

print("=== Тест 1 ===")

path = "./data/data_2.csv"
df = pd.read_csv(path, dtype=float)
data = df.to_numpy()

print("Путь до файла со входными данными: ", path)
print("Входное значение: ", 100)
print("Искомое значение: ", 100)
print("Значение интерполяции сплайном: ", "%.3E" % Decimal(SplineInterpolation(data).get_result_by_value(100)))
print()

print("=== Тест 2 ===")

path = "./data/data_3.csv"
df = pd.read_csv(path, dtype=float)
data = df.to_numpy()

print("Путь до файла со входными данными: ", path)
print("Входное значение: ", 3)
print("Искомое значение: ", -8)
print("Значение интерполяции сплайном: ", "%.3E" % Decimal(SplineInterpolation(data).get_result_by_value(3)))
print()

print("=== Тест 3 ===")

path = "./data/data_3.csv"
df = pd.read_csv(path, dtype=float)
data = df.to_numpy()

print("Путь до файла со входными данными: ", path)
print("Входное значение: ", 4)
print("Искомое значение: ", -15)
print("Значение интерполяции сплайном: ", "%.3E" % Decimal(SplineInterpolation(data).get_result_by_value(4)))
print()
