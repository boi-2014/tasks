import glob, re
FN_PATTERN = re.compile(r'^friends\.(\d{2})p?-(.*)\.in$')

def check_file(fn, subtask):
    print 'SUBTASK', subtask, fn,
    f = open(fn)
    n = int(f.readline().replace("\n", ""))
    s = f.readline().replace("\n", "")
    #print n, s, 
    assert 2 <= n <= 2000001
    assert len(s) == n
    if 2 <= n <= 2001:
        actual_subtask = 1
    elif 2 <= n <= 2000001:
        actual_subtask = 2
    else:
        actual_subtask = None
    if subtask != actual_subtask:
        print 'actual subtask: %d' % actual_subtask,
    f.close()
    print

for fn in glob.glob('friends.*.in'):
    matches = FN_PATTERN.match(fn)
    assert matches
    check_file(fn, int(matches.group(2)[0]))
