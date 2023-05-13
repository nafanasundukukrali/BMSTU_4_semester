import subprocess
import matplotlib.pyplot as plt
import statistics

ERROR_N = 4

size = int(input("Введите максимальный размер тестируемого массива:  "))
n = 10

subprocess.run(["cmake", f'-D', f'CMAKE_CXX_FLAGS="-DTEST_ARRAY_SIZE={size}"'])
subprocess.run(["make","-B"])
subprocess.run(["./lab_09"])
subprocess.run(["make","clean"])

with open("./results.txt", "r") as file:
    asm_data_x = [0 for _ in range(n)]
    file.readline()
    for i in range(n):
        for j in range(n):
            asm_data_x[j] += float(file.readline())

    for j in range(n):
        asm_data_x[j] /= n

    asm_data_cpp = [0 for i in range(n)]
    file.readline()
    for i in range(n):
        for j in range(n):
            asm_data_cpp[j] += float(file.readline())

    for j in range(n):
        asm_data_cpp[j] /= n

    y = [i for i in range(1, size, size // n)]

    plt.plot(y, asm_data_x, label='cpp')
    plt.plot(y, asm_data_cpp, label='asm')
    plt.legend()

    plt.show()
