import subprocess
import matplotlib.pyplot as plt
import statistics

ERROR_N = 4

n = int(input("Введите количество повторений исследований: "))

try:
    n = int(n)
except:
    print("ERROR: incorrect count input.")
    exit(ERROR_N)

if n <= 0:
    print("ERROR: incorrect count input.")
    exit(ERROR_N)

subprocess.run(["cmake", "-D", f'CMAKE_CXX_FLAGS="-DCOUNT={n}"'])
subprocess.run(["make","-B"])
subprocess.run(["./lab_08"])
subprocess.run(["make","clean"])

with open("./results.txt", "r") as file:
    buffer = file.readline()

    lines = file.readlines()
    i = 0

    data = {}

    mini = 10e+20

    while i < len(lines):
        label = buffer[:-1]
        buffer_res = []



        while i < len(lines):
            try:
                buffer_res.append(int(lines[i][:-1]))
                mini = min(buffer_res[-1], mini)
                i += 1
            except:
                buffer = lines[i]
                break

        if (buffer_res):
            result = statistics.median(buffer_res)
            data[label] = result

        i += 1

    # for key in data.keys():
    #     data[key] -= mini

    plt.bar(data.keys(), data.values())
    plt.show()
