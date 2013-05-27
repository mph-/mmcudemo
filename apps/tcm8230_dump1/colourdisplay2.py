import numpy as np
from matplotlib.pyplot import figure, show, savefig

# Camera data bus mapping, lsb first
bits = (0, 7, 6, 4, 1, 5, 3, 2)

pixmap = np.zeros(256, dtype=int)

for m in range(256):
    
    new = 0
    for bit, n in enumerate(bits):
        new = new + (((m & (1 << bit)) != 0) << n)

    pixmap[m] = new


imfile = open('/tmp/pic3.txt')
lines = imfile.readlines()
height = len(lines)

cimage = None

for r, line in enumerate(lines):
    (row, rowdata) = line.strip().split(':')
    raw = [pixmap[int(pix)] for pix in rowdata.split(',')[0: -1]]

    width = len(raw) / 2

    if cimage == None:
        cimage = np.zeros((width, height, 3), dtype=int)
        mimage = np.zeros((width, height), dtype=int)
        rimage = np.zeros((width, height), dtype=int)
        gimage = np.zeros((width, height), dtype=int)
        bimage = np.zeros((width, height), dtype=int)

    for p in range(width):
        x, y = raw[p * 2], raw[p * 2 + 1]
        red = x & 31
        green = ((y & 7) << 3) | (x >> 5)
        blue = y >> 3

        cimage[p, r, :] = (red, green, blue)
        rimage[p, r] = red << 3
        gimage[p, r] = green << 2
        bimage[p, r] = blue << 3
        mimage[p, r] = (red + green + blue) * 2



fig = figure()
ax = fig.add_subplot(111)
ax.imshow(cimage)


fig = figure()
ax = fig.add_subplot(111)
ax.imshow(mimage, cmap='gray')


show()


