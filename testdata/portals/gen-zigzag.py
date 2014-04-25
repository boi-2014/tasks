import sys

R = int(sys.argv[1])
C = int(sys.argv[2])

ar = [['.'] * C for _ in range(R)]
for r in range(R):
    for c in range(C):
        if ((r+c)%3 == 0) and ((c != 0 and r != R - 1) or (r+c)%6 == 0) and ((c != C - 1 and r != 0) or (r+c)%6 == 3):
            ar[r][c] = '#'
ar[0][2] = 'S'
ar[-1][-1] = 'C'

print(R, C)
for row in ar:
    print(''.join(row))
