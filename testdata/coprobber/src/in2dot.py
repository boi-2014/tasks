import sys
N = int(sys.stdin.readline())
lines = [map(int, sys.stdin.readline().split()) for i in xrange(N)]
sys.stdin.read()
print 'graph {'
for a in xrange(N):
    for b in xrange(a):
        if lines[a][b]:
            print '\t%d -- %d;' % (a, b)
print '}'
