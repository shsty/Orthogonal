#!/usr/bin/python3

from PIL import Image
import numpy as np

data = np.zeros((256, 256), dtype = np.uint8)

p = 3
n = 257

j = 1
for i in range(256):
    data[i,j-1] = 255;
    j = (j * p) % n

img = Image.fromarray(data, "L")
img.save("mask.png")
