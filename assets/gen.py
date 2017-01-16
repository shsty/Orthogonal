#/usr/bin/python3

from random import *

f = open("test.map", "w")

f.write("1 \n")

for i in range(16**4):
    if random() > 0.5:
        f.write("0 ")
    else:
        f.write("1 ")

f.close()
