# Subtask 1: trees. N <= 500

t1_1 = lambda: [
    (0, 1)
]

t1_2 = lambda: [
    (0, 1),
    (0, 2),
    (0, 3)
]

t1_3 = lambda: [
    (0, 2),
    (1, 2),
    (2, 4),
    (3, 4),
    (4, 5),
    (4, 6),
    (6, 7)
]

# 500-long straight line
t1_4 = lambda: [(x, x+1) for x in xrange(499)]

def random_tree(n):
    edges = []
    for i in xrange(1, n):
        edges.append((i, random.randrange(i)))
    remap = range(n)
    random.shuffle(remap)
    return [(remap[a], remap[b]) for a, b in edges]

t1_5 = lambda: random_tree(237)
t1_6 = lambda: random_tree(500)


# Subtask 2: grids. N <= 500

def grid(w, h):
    assert w * h <= 500
    edges = []
    for r in xrange(h):
        for c in xrange(w):
            this = w * r + c
            if c > 0:
                edges.append((this - 1, this))
            if r > 0:
                edges.append((this - w, this))
    return edges

t2_1 = lambda: grid(2, 2)
t2_2 = lambda: grid(4, 3)
t2_3 = lambda: grid(17, 29)
t2_4 = lambda: grid(2, 250)
t2_5 = lambda: grid(22, 22)
t2_6 = lambda: grid(166, 3)


# Subtask 3: N <= 100

def random_full(n):
    ds = DisjointSet()
    deg = [0] * n
    edges = []
    while not all(deg) or len(ds.group) > 1:
        edge = (random.randrange(n), random.randrange(n))
        if edge[0] == edge[1]:
            continue
        deg[edge[0]] += 1
        deg[edge[1]] += 1
        ds.add(*edge)
        edges.append(edge)
    return edges

def full_graph(n):
    return [(x, y) for x in xrange(n) for y in xrange(x + 1, n)]

def dup(edgelist):
    N = 1 + max(max(a, b) for a, b in edgelist)
    l = []
    for a, b in edgelist:
        l.append((a, b))
        l.append((a + N, b + N))
    for i in xrange(N):
        l.append((i, i + N))
    return l

def many_edges(n, m):
    ds = DisjointSet()
    deg = [0] * n
    edges = []
    while not all(deg) or len(ds.group) > 1 or m > 0:
        edge = (random.randrange(n), random.randrange(n))
        if edge[0] == edge[1]:
            continue
        deg[edge[0]] += 1
        deg[edge[1]] += 1
        ds.add(*edge)
        edges.append(edge)
        m -= 1
    return edges

# Triangle
t3_1 = lambda: [(0, 1), (0, 2), (1, 2)]
# Cube
t3_2 = lambda: dup(dup([(0, 1)]))
# Pentagon
t3_3 = lambda: [(0, 1), (1, 2), (2, 3), (3, 4), (4, 0)]
t3_4 = lambda: random_full(10)
t3_5 = lambda: random_full(23)
t3_6 = lambda: random_full(77)
t3_7 = lambda: random_full(100)
t3_8 = lambda: many_edges(100, 100*100/3)


# Subtask 4: N <= 500

t4_1 = lambda: random_full(200)
t4_2 = lambda: random_full(400)
t4_3 = lambda: random_full(500)
t4_4 = lambda: full_graph(500)
t4_5 = lambda: many_edges(450, 450*450/4)
t4_6 = lambda: many_edges(500, 500*500/6)

PUBLIC_TESTS = [(1, 2)]

TESTS = [
    [t1_1, t1_2, t1_3, t1_4, t1_5, t1_6],
    [t2_1, t2_2, t2_3, t2_4, t2_5, t2_6],
    [t3_1, t3_2, t3_3, t3_4, t3_5, t3_6, t3_7, t3_8],
    [t4_1, t4_2, t4_3, t4_4, t4_5, t4_6],
]

def print_test(f, edgelist):
    N = 1 + max(max(a, b) for a, b in edgelist)
    print >>f, N
    adj = [['0'] * N for i in xrange(N)]
    ds = DisjointSet()
    for a, b in edgelist:
        assert a != b
        adj[a][b] = adj[b][a] = '1'
        ds.add(a, b)
    assert len(ds.group) == 1
    for r in adj:
        assert any(x == '1' for x in r)
        print >>f, ' '.join(r)

def run():
    import sys, subprocess, cStringIO, shutil
    
    subtask4_additional = []
    
    for subtask, tests in enumerate(TESTS, start=1):
        if subtask == 4:
            tests = tests + subtask4_additional
        for i, test in enumerate(tests, start=1):
            filename = '../coprobber.%d-%02d' % (subtask, i)
            if (subtask, i) in PUBLIC_TESTS:
                filename += 'p'
            print >>sys.stderr, filename
            if subtask < 4:
                subtask4_additional.append(filename)
            if callable(test):
                sio = cStringIO.StringIO()
                print_test(sio, test())
                with open(filename + '.in', 'w') as f:
                    st = getattr(test, 'robber_strategy', 0)
                    p = subprocess.Popen(['add_robber_strategy', str(st)],
                        stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                        universal_newlines=True)
                    stdout = p.communicate(sio.getvalue())[0]
                    lines = stdout.split('\n')
                    print lines[int(lines[0]) + 1]
                    f.write(stdout)
            else:
                shutil.copyfile(test + '.in', filename + '.in')
            with open(filename + '.sol', 'w') as f:
                print >>f, 1 if subtask >= 3 else 0

import random
random.seed(1382525932)  # Make the generator deterministic

class DisjointSet(object):
    def __init__(self):
        self.leader = {} # maps a member to the group's leader
        self.group = {} # maps a group leader to the group (which is a set)

    def add(self, a, b):
        leadera = self.leader.get(a)
        leaderb = self.leader.get(b)
        if leadera is not None:
            if leaderb is not None:
                if leadera == leaderb: return # nothing to do
                groupa = self.group[leadera]
                groupb = self.group[leaderb]
                if len(groupa) < len(groupb):
                    a, leadera, groupa, b, leaderb, groupb = b, leaderb, groupb, a, leadera, groupa
                groupa |= groupb
                del self.group[leaderb]
                for k in groupb:
                    self.leader[k] = leadera
            else:
                self.group[leadera].add(b)
                self.leader[b] = leadera
        else:
            if leaderb is not None:
                self.group[leaderb].add(a)
                self.leader[a] = leaderb
            else:
                self.leader[a] = self.leader[b] = a
                self.group[a] = set([a, b])


if __name__ == '__main__':
    run()
