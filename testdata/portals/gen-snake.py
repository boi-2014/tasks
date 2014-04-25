import sys

R = int(sys.argv[1])
C = int(sys.argv[2])

ar = [['.'] * C for _ in range(R)]
for r in range(1, R, 2):
    for c in range((r%4 == 3), C - (r%4 == 1)):
        ar[r][c] = '#'
ar[0][0] = 'S'
ar[-1][(C-1)*((R-1)%4 < 2)] = 'C'

print('{} {}'.format(R, C))
for row in ar:
    print(''.join(row))
