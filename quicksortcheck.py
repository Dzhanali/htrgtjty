import random as rd
import subprocess


while True:
    req = input("check/quit?\n")
    if req == "check":
        f1 = open("inputquick.txt", 'w')
        f1.write("500\n")
        init = []
        for i in range(500):
            f1.write("100\n")
            init.append([rd.randint(0, 1000) for j in range(100)])
            f1.write(' '.join(map(str, init[i])) + '\n')
            init[i].sort()
        f1.close()
        subprocess.run(['quick.exe', '-o', 'quick.o'])
        f2 = open("outputquick.txt", 'r')
        shell = f2.readlines()
        outp = [list(map(int, shell[i][:-1].split())) for i in range(len(shell) - 1) if shell[i][0] != 't' and shell[i][0] != 'a']
        print(init == outp)
        print(shell[-1])
        f2.close()
    elif req == "quit":
        break
