from __future__ import division
import sys
import random

R = int(sys.argv[1])
C = int(sys.argv[2])
allow_four_crossing = bool(int(sys.argv[3])) # 0 for subtask 3; otherwise there will be squares with no wall nearby
holes = int(sys.argv[4]) # approximate number of # tiles that are converted into . (giving more freedom in pathfinding)
seed = int(sys.argv[5])

random.seed(seed)

x = random.randrange(C)
y = random.randrange(R)

ar = [['#'] * C for _ in range(R)]

Dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
def oob(el):
	global R, C
	return el[0] < 0 or el[1] < 0 or el[0] >= C or el[1] >= R

def count_adj(el):
	global Dirs, ar
	count = 0
	for d in Dirs:
		el2 = (el[0] + d[0], el[1] + d[1])
		if oob(el2):
			continue
		if ar[el2[1]][el2[0]] == '.':
			count += 1
	return count

mdist = -1
furthest = None

st = [(x, y, 0)]
while st:
	el = st.pop()
	if ar[el[1]][el[0]] == '.' or count_adj(el) > 1:
		continue
	ar[el[1]][el[0]] = '.'
	dist = el[2]
	if dist > mdist:
		furthest = el
		mdist = dist
	dirs = Dirs[:]
	random.shuffle(dirs)
	count = 0
	for d in dirs:
		el2 = (el[0] + d[0], el[1] + d[1], dist + 1)
		if not oob(el2) and count_adj(el2) <= 1:
			st.append(el2)
			count += 1
			if count == 2 and not allow_four_crossing:
				break

ar[y][x] = 'S'
ar[furthest[1]][furthest[0]] = 'C'

for i in range(holes):
	x = random.randrange(C)
	y = random.randrange(R)
	el = (x, y)
	if ar[y][x] != '#' or (count_adj(el) == 4 and not allow_four_crossing):
		continue
	fail = False
	for d in Dirs:
		el2 = (el[0] + d[0], el[1] + d[1])
		if not oob(el2) and count_adj(el2) == 3 and not allow_four_crossing:
			fail = True
			break
	if fail:
		continue
	ar[y][x] = '.'

print('{} {}'.format(R, C))
for row in ar:
	print(''.join(row))

