import random as rd
import subprocess


while True:
    req = input("check/quit?\n")
    if req == "check":
        subprocess.run(['heap.exe', '-o', 'heap.o'])
        f1 = open("ansBFS.txt", 'r')
        f2 = open("outputBFS.txt", 'r')
        ans = f1.readlines()
        outp = f2.readlines()
        print(ans == outp)
        f1.close()
        f2.close()
    elif req == "quit":
        break
