import os


def main():
    listCalc = 0
    listResult = [[], []]

    subsTypes = ['/normal_sub/', '/shared_sub/']
    scenarios = [1, 2, 3, 4, 5, 6]
    messages = [2, 10, 50, 100]

    count = 0

    for j in subsTypes:
        for i in scenarios:
            for k in messages:
                path = "/home/marceloek/Desktop/TCC_II_Experimento/result/" + \
                    str(i) + j + str(k) + '/'

                dirList = os.listdir(path)
                validFiles = len(dirList)

                for resultFileCSV in dirList:
                    with open(path + resultFileCSV) as result:
                        lines = result.readlines()
                        if (len(lines) < 2000):
                            validFiles -= 1
                            continue

                        totalLatency = (
                            float(lines[-1].split(',')[0]) - float(lines[0].split(',')[0]))

                        listCalc += totalLatency

                listResult[count].append(listCalc / validFiles)
                listCalc = 0
        count += 1

    count = 0
    countMessages = 0

    pathResultFile = '/home/marceloek/Desktop/TCC_II_Experimento/result/resultScenarios.txt'
    f = open(pathResultFile, 'w')

    for x in range(0, len(scenarios) * len(messages)):
        if((x % 4) == 0):
            f.write('\nScenario: [' + str(scenarios[count]) + ']\n')
            count += 1
            countMessages = 0

        f.write(str(listResult[0][x]) + ',' + str(listResult[1][x]) + '\n')
        f.write('Number Messages [' + str(messages[countMessages]) + ']: ' +
                str((listResult[0][x] - listResult[1][x]) / 1000) + ' ms\n')

        countMessages += 1

    f.close()

    f = open(pathResultFile, 'r')
    print(f.read())
    f.close()


main()
