import sys

R = int(sys.argv[1])
C = int(sys.argv[2])

ar = [['.'] * C for _ in range(R)]
for r in range(1, R):
    ar[r][-3] = '#'
    if (r % 2):
        ar[r][-2 + (r%4 == 3)] = '#'
ar[0][0] = 'S'
ar[-1][-1 - ((R-1)%4 > 1)] = 'C'

print('{} {}'.format(R, C))
for row in ar:
    print(''.join(row))
