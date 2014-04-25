import glob, re

FN_PATTERN = re.compile(r'^senior\.(\d)-(\d{2})p?\.in$')

def check_file(fn, subtask):
    print 'SUBTASK', subtask, fn,
    f = open(fn)
    n, m = map(int, f.readline().split())
    if 1 <= n <= 2000 and 1 <= m <= 10**5:
        actual_subtask = 1
    elif 1 <= n <= 10**5 and 1 <= m <= 10**5:
        actual_subtask = 2
    elif 1 <= n <= 10**6 and 1 <= m <= 10**6:
        actual_subtask = 3
    else:
        actual_subtask = None
    if subtask != actual_subtask:
        print 'actual subtask: %d' % actual_subtask,
    edges = [map(int, f.readline().split()) for i in xrange(m)]
    edgeset = set()
    degrees = [0] * n
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
    for d in degrees:
        assert d % 2 == 0
    f.close()
    print

for fn in glob.glob('senior.*.in'):
    matches = FN_PATTERN.match(fn)
    assert matches
    check_file(fn, int(matches.group(1)))