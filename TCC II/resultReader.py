import os

listCalc = 0
listResult = [[], []]

subsTypes = ['/normal_sub/', '/shared_sub/']
scenarios = [1, 2, 3, 4]
messages = [2, 10, 50, 100]

count = 0

for j in subsTypes:
    for i in scenarios:
        for k in messages:
            path = "/home/marceloek/Desktop/result/" + \
                str(i) + j + str(k) + '/'

            dirList = os.listdir(path)

            for resultFileCSV in dirList:
                with open(path + resultFileCSV) as result:
                    lines = result.readlines()
                    totalLatency = (
                        float(lines[-1].split(',')[0]) - float(lines[0].split(',')[0])) / 100

                    listCalc += totalLatency

            listResult[count].append(listCalc / 10)
            listCalc = 0
    count += 1

for x in range(0, len(scenarios) * len(messages)):
    print((listResult[0][x] - listResult[1][x]) / 10000, 'ms')

# print(listResult[0])
# print(listResult[1])
