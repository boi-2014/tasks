import glob, re

class DisjointSets:
    def __init__ (self, N):
        self.p = [-1] * (N+1)

    def findP (self, v):
        a = v
	while (self.p[a] != -1):
	    a = self.p[a]
	while (self.p[v] != -1):
	    u = v
	    v = self.p[v]
	    self.p[u] = a
	return a
    
    def equal (self, a, b):
    	return self.findP(a) == self.findP(b)

    def add (self, a, b):
    	pa, pb = self.findP(a), self.findP(b)
	if (pa != pb):
	    self.p[pa] = pb


FN_PATTERN = re.compile(r'^postmen_\.(\d{2})p?-(.*)\.in$')

def check_file(fn, subtask):
    print 'SUBTASK', subtask, fn,
    f = open(fn)
    n, m = map(int, f.readline().split())
    if 1 <= n <= 2000 and 1 <= m <= 10**5:
        actual_subtask = 1
    elif 1 <= n <= 10**5 and 1 <= m <= 10**5:
        actual_subtask = 2
    elif 1 <= n <= 5 * 10**5 and 1 <= m <= 5 * 10**5:
        actual_subtask = 3
    else:
        actual_subtask = None
    if subtask != actual_subtask:
        print 'actual subtask: %d' % actual_subtask,
    edges = [map(int, f.readline().split()) for i in xrange(m)]
    edgeset = set()
    degrees = [0] * n
    D = DisjointSets(n)
    for ea, eb in edges:
        assert 1 <= ea <= n
        assert 1 <= eb <= n
        assert ea != eb
        assert (ea, eb) not in edgeset
        assert (eb, ea) not in edgeset
        edgeset.add((ea, eb))
        edgeset.add((eb, ea))
        degrees[ea-1] += 1
        degrees[eb-1] += 1
	D.add(ea, eb)
    for d in degrees:
        assert d % 2 == 0
    	assert d != 0
    for i in xrange (2, n + 1):
        assert D.equal(1, i)
    f.close()
    print

for fn in glob.glob('postmen_.*.in'):
    matches = FN_PATTERN.match(fn)
    assert matches
    check_file(fn, int(matches.group(2)[0]))
