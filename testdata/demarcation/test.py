import glob, re, sys, subprocess

FN_PATTERN = re.compile(r'^FINAL\\demarcation\.(\d{2})p?-(.*)\.in$')

def check_file(fn, subtask_str):
    print 'SUBTASK', subtask_str, fn, ":",
    f = open(fn)
    N = int(f.readline())
    
    assert 4 <= N <= 100000
    if 4 <= N <= 200:
        actual_subtask = 2	
    elif 4 <= N <= 4000:
        actual_subtask = 3
    elif 4 <= N <= 100000:
        actual_subtask = 4
    else:
        actual_subtask = -999
    
    subtask = int(subtask_str.replace("1","")[0])

    if subtask != actual_subtask:
        print 'actual subtask: %d' % actual_subtask

    S = set()
    for xxx in range (N):
        x, y = map(int, f.readline().split())
        assert (x, y) not in S
        S.add((x, y))
    
    output = subprocess.check_output (['validator.exe', fn, subtask_str], shell=True)
    assert output == "OK"
    print output 


for fn in glob.glob('FINAL/demarcation.*.in'):
    matches = FN_PATTERN.match(fn)
    assert matches
    check_file(fn, matches.group(2))
