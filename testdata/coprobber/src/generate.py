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

PUBLIC_TESTS = [(1, 2)]

TESTS = [
    [t1_1, t1_2, t1_3, t1_4, t1_5, t1_6],
    [t2_1, t2_2, t2_3, t2_4, t2_5, t2_6],
    [
    
    ],
    [
    
    ],
]

def print_test(f, edgelist):
    N = 1 + max(max(a, b) for a, b in edgelist)
    print >>f, N
    adj = [['0'] * N for i in xrange(N)]
    for a, b in edgelist:
        assert a != b
        adj[a][b] = adj[b][a] = '1'
    for r in adj:
        assert any(x == '1' for x in r)
        print >>f, ' '.join(r)

def run():
    import sys, subprocess, cStringIO, itertools
    
    # Last subtask includes tests from all subtasks
    TESTS[3] = list(itertools.chain.from_iterable(TESTS))
    
    for subtask, tests in enumerate(TESTS, start=1):
        for i, test in enumerate(tests, start=1):
            filename = '../coprobber.%d-%02d' % (subtask, i)
            if (subtask, i) in PUBLIC_TESTS:
                filename += 'p'
            print >>sys.stderr, filename
            sio = cStringIO.StringIO()
            print_test(sio, test())
            with open(filename + '.in', 'w') as f:
                st = getattr(test, 'robber_strategy', 0)
                p = subprocess.Popen(['add_robber_strategy', str(st)],
                    stdin=subprocess.PIPE, stdout=f)
                p.communicate(sio.getvalue())
            with open(filename + '.sol', 'w') as f:
                print >>f, 1 if subtask >= 3 else 0

import random

if __name__ == '__main__':
    run()
