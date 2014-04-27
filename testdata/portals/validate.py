import glob, re, sys, subprocess

FN_PATTERN = re.compile(r'^tests\\portals\.(\d{2})p?-(.*)\.in$')

def check_file(fn, subtask_str):
    print 'SUBTASK', subtask_str, fn, ":",
    f = open(fn)
    R, C = map (int, f.readline().split())

    assert 1 <= R <= 1000 and 1 <= C <= 1000
    if 1 <= R <= 10 and 1 <= C <= 10:
        actual_subtask = 1
    elif 1 <= R <= 50 and 1 <= C <= 50:
        actual_subtask = 2
    elif 1 <= R <= 200 and 1 <= C <= 200:
        actual_subtask = 4
    elif 1 <= R <= 1000 and 1 <= R <= 1000:
        actual_subtask = 5
    else:
        actual_subtask = -999
    
    subtask = int(subtask_str.replace("3","")[0])

    if subtask != actual_subtask:
        print 'actual subtask: %d' % actual_subtask,

    A = [['#']*(C+2)]
    for i in xrange(R):
        A.append("#" + f.readline().replace("\n","") + "#")
        assert len(A[-1:][0]) == C+2
    A.append(['#']*(C+2))
    assert len(A) == R+2

    S, CC = 0, 0
    Sc, Cc = 0, 0
    for r, x in enumerate(A):
        if (x.count("S") > 0):
            Sc = (r, x.find("S"))
            S += x.count("S")
        if (x.count("C") > 0):
            Cc = (r, x.find("C"))
            CC += x.count("C")
    assert S == 1 and CC == 1
    assert A[Sc[0]][Sc[1]] == 'S'
    assert A[Cc[0]][Cc[1]] == 'C'

    good = True
    for x in xrange (1, R + 2):
        #print A[x], x,
        for y in xrange (1, C + 1):
            #print A[x][y]
            if A[x][y] == "." or A[x][y] == 'S' or A[x][y] == 'C':
                good = good and (A[x+1][y]=='#' or A[x-1][y]=='#' or A[x][y+1]=='#' or A[x][y-1]=='#')
                #if x == 3 and y == 4:
                    #print (A[x+1][y]=='#' or A[x-1][y]=='#' or A[x][y+1]=='#' or A[x][y-1]=='#')
            #print 
    
    if "3" in subtask_str:
        assert good
    if ("3" not in subtask_str) and good and actual_subtask <= 4:
        print "(in 3rd as well)",

    dist = [[1000000]*(C+2) for x in xrange(R+2)]

    Q = [Sc]
    dist[Sc[0]][Sc[1]] = 0
    while (len(Q) > 0):
        v = Q[0]
        Q = Q[1:]
        for e in [(1,0),(0,1),(-1,0),(0,-1)]:
            u = (v[0] + e[0], v[1] + e[1])
            if A[u[0]][u[1]] == '#':
                continue
            if dist[u[0]][u[1]] > dist[v[0]][v[1]] + 1:
                dist[u[0]][u[1]] = dist[v[0]][v[1]] + 1
                Q.append(u)
    assert dist[Cc[0]][Cc[1]] < 1000000
    print 

for fn in glob.glob('tests/portals.*.in'):
    matches = FN_PATTERN.match(fn)
    assert matches
    check_file(fn, matches.group(2))
