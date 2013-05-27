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

# pic4 bw
imfile = open('/tmp/pic4.txt')
#imfile = open('/tmp/tmp.img')
lines = imfile.readlines()
height = len(lines)

image = None

for r, line in enumerate(lines):
    (row, rowdata) = line.strip().split(':')
    raw = [pixmap[int(pix)] for pix in rowdata.split(',')[0: -1]]

    width = len(raw) / 2

    if image == None:
        image = np.zeros((width, height, 3), dtype=int)
        rawx = np.zeros((width, height), dtype=int)
        rawy = np.zeros((width, height), dtype=int)
        rimage = np.zeros((width, height), dtype=int)
        gimage = np.zeros((width, height), dtype=int)
        bimage = np.zeros((width, height), dtype=int)

    for p in range(width):
        x, y = raw[p], raw[width + p]
        rimage[p, r] = x & 31
        rawx[p, r] = x
        rawy[p, r] = y


fig = figure()
ax = fig.add_subplot(111)
ax.imshow(rawx, cmap='gray')
show()


