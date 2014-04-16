from __future__ import division
import sys
import random

R = int(sys.argv[1])
C = int(sys.argv[2])
p = int(sys.argv[3]) # approximate number of # tiles
should_fill = bool(int(sys.argv[4])) # 1 to generate a fractal-like structure (not really an interesting test case, but anyhow)
seed = int(sys.argv[5])

random.seed(seed)

def rx():
	return random.randrange(C)
def ry():
	return random.randrange(R)

ar = [['.'] * C for _ in range(R)]

def fill(x0, y0, x1, y1):
	smallLim = 5
	dx, dy = x1 - x0, y1 - y0
	if dx < smallLim or dy < smallLim:
		return
	xm = (x0 + x1) // 2
	ym = (y0 + y1) // 2
	xl = (3*x0+x1) // 4
	xh = (x0+3*x1) // 4 + 1
	yl = (3*y0+y1) // 4
	yh = (y0+3*y1) // 4 + 1
	D = random.choice([1,2,3,4])
	if D == 1: xl = x0
	if D == 2: xh = x1
	if D == 3: yl = y0
	if D == 4: yh = y1
	for x in range(xl, xh):
		ar[ym][x] = '#'
	for y in range(yl, yh):
		ar[y][xm] = '#'

	fill(x0, y0, xm, ym)
	fill(xm+1, y0, x1, ym)
	fill(x0, ym+1, xm, y1)
	fill(xm+1, ym+1, x1, y1)

if should_fill:
	fill(0, 0, C, R)

for _ in range(p):
	x, y = rx(), ry()
	r = random.random()
	vertical = False # (r < 0.3)
	horizontal = False # not vertical and (r < 0.6)
	if vertical:
		for y_ in range(y-2, y+3):
			if y_ >= 0 and y_ < R:
				ar[y_][x] = '#'
	elif horizontal:
		for x_ in range(x-2, x+3):
			if x_ >= 0 and x_ < C:
				ar[y][x_] = '#'
	else:
		ar[y][x] = '#'

ar[ry()][rx()] = 'S'
ar[ry()][rx()] = 'C'

print('{} {}'.format(R, C))
for row in ar:
	print(''.join(row))
