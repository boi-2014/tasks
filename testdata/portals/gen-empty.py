from __future__ import division
import sys

R = int(sys.argv[1])
C = int(sys.argv[2])

ar = [['.'] * C for _ in range(R)]
for r in range(R):
	ar[r][-3] = '#'
for h in range(C*2 // 3, C*3 // 4):
	ar[h][-3] = '.'
ar[-2][-1] = 'C'
ar[R // 2][C // 2 - 4] = 'S'
ar[-2][C // 2 - 3] = '#'

print('{} {}'.format(R, C))
for row in ar:
	print(''.join(row))
