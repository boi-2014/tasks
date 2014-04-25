import sys

R = int(sys.argv[1])
C = int(sys.argv[2])

ar = [['.'] * C for _ in range(R)]
for r in range(R):
    ar[r][C // 2] = '#'
y = (C // 4) * 2 + 1
ar[y][C // 2] = '.'
for r in range(1, R, 2):
    for c in range(C // 2 - 1):
        ar[r][c] = '#'
ar[0][0] = 'S'
x = C // 4 * 3 + 1
ar[R // 4][x] = '#'
ar[R // 4 + 1][x] = 'C'

print(R, C)
for row in ar:
    print(''.join(row))
