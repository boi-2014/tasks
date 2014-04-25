tests = []

# Subtask 1: trees. N <= 500

tests.append((lambda: [
    (0, 1)
], (1, 3, 4)))

t = lambda: [
    (0, 1),
    (0, 2),
    (0, 3)
]
t.public = True
tests.append((t, (1, 3, 4)))

tests.append((lambda: [
    (0, 2),
    (1, 2),
    (2, 4),
    (3, 4),
    (4, 5),
    (4, 6),
    (6, 7)
], (1, 3, 4)))

# 500-long straight line
tests.append((lambda: [(x, x+1) for x in xrange(499)], (1, 4)))

def random_tree(n):
    edges = []
    for i in xrange(1, n):
        edges.append((i, random.randrange(i)))
    remap = range(n)
    random.shuffle(remap)
    return [(remap[a], remap[b]) for a, b in edges]

tests.append((lambda: random_tree(237), (1, 4)))
tests.append((lambda: random_tree(500), (1, 4)))


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

tests += [
    (lambda: grid(2, 2), (2, 3, 4)),
    (lambda: grid(4, 3), (2, 3, 4)),
    (lambda: grid(17, 29), (2, 4)),
    (lambda: grid(2, 250), (2, 4)),
    (lambda: grid(22, 22), (2, 4)),
    (lambda: grid(166, 3), (2, 4)),
]


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

tests += [
    # Triangle
    (lambda: [(0, 1), (0, 2), (1, 2)], (3, 4)),
    # Cube
    (lambda: dup(dup([(0, 1)])), (3, 4)),
    # Pentagon
    (lambda: [(0, 1), (1, 2), (2, 3), (3, 4), (4, 0)], (3, 4)),
    (lambda: random_full(10), (3, 4)),
    (lambda: random_full(23), (3, 4)),
    (lambda: random_full(77), (3, 4)),
    (lambda: random_full(100), (3, 4)),
    (lambda: many_edges(100, 100*100/3), (3, 4)),
]


# Subtask 4: N <= 500

tests += [
    (lambda: random_full(200), (4,)),
    (lambda: random_full(400), (4,)),
    (lambda: random_full(500), (4,)),
    (lambda: full_graph(500), (4,)),
    (lambda: many_edges(450, 450*450/4), (4,)),
    (lambda: many_edges(500, 500*500/6), (4,)),
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

def cop_wins(output):
    lines = output.split('\n')
    return lines[int(lines[0]) + 1] == '1'

def add_strategy(input, strategy_num):
    import subprocess
    p = subprocess.Popen(['add_robber_strategy', str(strategy_num)],
        stdin=subprocess.PIPE, stdout=subprocess.PIPE,
        universal_newlines=True)
    return p.communicate(input)[0]

def run():
    import sys, cStringIO, shutil
    
    for test_num, (test_func, subtasks) in enumerate(tests, start=1):
        public = 'p' if getattr(test_func, 'public', None) else ''
        subtasks = ''.join(str(x) for x in sorted(subtasks))
        filename = '../coprobber.%02d%s-%s' % (test_num, public, subtasks)
        print >>sys.stderr, filename
        
        sio = cStringIO.StringIO()
        print_test(sio, test_func())
        st = getattr(test_func, 'robber_strategy', 0)
        stdout = add_strategy(sio.getvalue(), st)
        print cop_wins(stdout)
        with open(filename + '.in', 'w') as f:
            f.write(stdout)

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

import random

if __name__ == '__main__':
    random.seed(1382525932)  # Make the generator deterministic
    run()
