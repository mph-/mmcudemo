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
#imfile = open('/tmp/tmp.img')
lines = imfile.readlines()
height = len(lines)

image = None

for r, line in enumerate(lines):
    (row, rowdata) = line.strip().split(':')
    raw = [pixmap[int(pix)] for pix in rowdata.split(',')[0: -1]]

    width = len(raw) / 2

    if image == None:
        image = np.zeros((width, height), dtype=int)

    for p in range(width):
        x, y = raw[p * 2], raw[p * 2 + 1]
        red = x >> 3
        green = ((x & 7) << 3) + (y >> 5)
        green = (x & 7) + ((y >> 5) << 3)
        blue = y & 31
        pix = (red + green + blue) * 2
#        if pix > 127:
#            pix = 127
        image[p, r] = pix



fig = figure()
ax = fig.add_subplot(111)
ax.imshow(image.T, cmap='gray')
show()


