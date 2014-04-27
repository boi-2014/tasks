import random

def full_graph (N):
	adj = []
	for i in range (1, N+1):
		for j in range (i + 1, N + 1):
			adj.append((i, j))
	print "Full graph N = %d generated" % N
	return (N, (N*(N-1))/2, adj)


def paths_len3 (N):
	if (N % 2) == 0:
		N -= 1
	adj = []
	for i in range (2, N+1, 2):
		adj.append((1,i))
		adj.append((1,i + 1))
		adj.append((i,i + 1))
	print "Graph of cycles=3, N = %d" % N
	return (N, 3*(N-1)/2, adj)

def ring (N):
	adj = []
	for i in range (1, N):
		adj.append((i, i + 1))
	adj.append((1, N))
	print "Ring of N = %d" % N
	return (N, N, adj)

def ring_of_rings(N_rings):
	N = 3*N_rings
	adj = []
	for i in range(0, N, 3):
		adj.append((i+1, i+2))
		adj.append((i+1, i+3))
		if (i+1 != N-2):
			adj.append((i+2, i+4))
			adj.append((i+3, i+4))
	adj.append((3*N_rings, 1))
	adj.append((3*N_rings-1, 1))
	print "Ring of rings N_rings = %d" % N_rings
	return (N, len(adj), adj)

def getU (v, p):
	return p[p[1]!=v]

def find_cycle (N, k):
	visited = [0 for i in range (N + 1)]
	v = random.randint (1, N);
	cycle = [v]
	p = -1
	FULL = set ( range(1, N + 1) )
	
	while (True):
		visited[v] = True
		neigh = list ( FULL - k[v] - set([v]) )
		random.shuffle(neigh)
		if (len(neigh)==0):
			return False

		for u in neigh:
			k[u].add(v)
			k[v].add(u)

			if not visited[u]:
				cycle.append(u)
				v = u
				break
			else:
				ans = cycle[cycle.index(u):]
				for x in range(cycle.index(u)):
					k[cycle[x]].remove(cycle[x+1])
					k[cycle[x+1]].remove(cycle[x])
				return (ans, k)
	return False

def rand_small_graph (N, M):
	
	k = [set() for x in xrange (N+1)]
	adj = []
	for i in xrange (1, N):
		k[i].add(i+1)
		k[i+1].add(i)
		adj.append((i, i+1))
	k[1].add(N)
	k[N].add(1)
	adj.append((1, N))

	b = find_cycle(N, k)
	while (b != False):
		k = b[1]
		if (len(b[0]) + len(adj) > M):
			break
		for i in range(len(b[0])):
			adj.append((b[0][i], b[0][(i+1)%len(b[0])]))
		b = find_cycle(N, k)
	
	print "Rand graph small N = %d, M = %d" % (N, len(adj))
	return (N, len(adj), adj)	

def dense_small_graph (N, M):
	K = M / N
	if (K > N - 1):
		K = N - 1
	adj = []
	for i in range (1, N+1):
		for j in range (i + 1, i + K + 1):
			t = (j, j-N)[j>N]
			adj.append([i, t])
	print "Dense small graph N = %d" % N
	return (N, len(adj), adj)

def tree_graph (N):
	M = 3*N - 3
	ret = []
	V = 1
	for i in range (2, N + 1):
		ret.append((random.randint(1, V), i))
		V += 1
	for xxx in range(N-1):
		e = ret[xxx] 
		V += 1
		ret.append((e[0], V))
		ret.append((e[1], V))
	return (2*N-1, len(ret), ret)

def click_graph (N1):
	M = 4 * N1
	N1 = M/4
	ret = []
	for i in range (1,N1):
		ret.append( (i, i + 1) )
	ret.append( (1, N1) )
	for i in range (1, N1 + 1):
		ret.append( (i,i+N1) )
		ret.append( (i,i+2*N1) )
		ret.append( (i+N1, i+2*N1) )
	return (3*N1, len(ret), ret)


def print_test (T, filename):
	file = open(filename, "w")
	file.write(str(T[0]) + " " + str(T[1]) + "\n")
	for p in T[2]:
		file.write(str(p[0]) + " " + str(p[1]) + "\n")
	file.close()


def print_tests(T):
	template = "postmen_.%02d%s-%s.in"
	ss = "123"
	K = 1
	for subtask, t in enumerate(T):
		for tnr, test in enumerate(t):
			filename = template % (K, ("","p")[K==1], ss)
			file = open(filename, "w")
			file.write(str(test[0]) + " " + str(test[1]) + "\n")
			random.shuffle(test[2])
			for edge in test[2]:
				file.write(str(edge[0]) + " " + str(edge[1]) + "\n")
			file.close()
			K += 1
		ss = ss[1:]
"""
print rand_small_graph(10, 20)
print tree_graph(6)
print click_graph(12)
exit()
"""

T = [[],[],[]]

MAX_N = [2000, 100000, 500000]
MAX_M = [100000, 100000, 500000]

print "GENERATING SUBTASK 1:"

#public test case
T[0].append((10, 15, [[1,2],[1,3],[4,2],[5,2],[3,5],[6,2],[7,5],[3,8],[5,8],[3,7],
					  [6,7],[8,7],[4,9],[9,10],[10,8]]))
#triangle
T[0].append((3, 3, [[1,2],[2,3],[3,1]]))

#3 squares making a triangle in the middle
T[0].append((9, 12, [[1,2],[2,3],[3,4],[4,1],[4,5],[5,6],[6,7],[7,4],[3,7],[7,8],[8,9],[3,9]]))

#K5 - star (pentagram):
T[0].append(full_graph(5))

T[0].append(paths_len3(MAX_N[0]))

T[0].append(rand_small_graph(50, 10000))
T[0].append(rand_small_graph(100, 10000))
T[0].append(rand_small_graph(MAX_N[0], 15000))
T[0].append(ring(MAX_N[0]))
T[0].append(full_graph(447))
T[0].append(tree_graph(MAX_N[0]/2-1))
T[0].append(click_graph( MAX_N[0]/3 ))

#1->(2,3,..,K+1), 2->(3,4,..,K+2)
T[0].append(dense_small_graph(MAX_N[0], MAX_M[0]))


print "\nGENERATING SUBTASK 2:"

T[1].append(ring(MAX_N[1]))
T[1].append(ring_of_rings(MAX_N[1]/4))
T[1].append(paths_len3(2*MAX_M[1]/3+1))
T[1].append(dense_small_graph(MAX_N[1], MAX_M[1]))
T[1].append(tree_graph( MAX_N[1]/3-1 ))
T[1].append(click_graph( min(MAX_M[1]/4, MAX_N[1]) ))

print "\nGENERATING SUBTASK 3:"

T[2].append(ring(MAX_N[2]))
T[2].append(ring_of_rings(MAX_N[2]/4))
T[2].append(paths_len3(2*MAX_M[2]/3+1))
T[2].append(dense_small_graph(MAX_N[2], MAX_M[2]))
T[2].append(tree_graph( MAX_N[2]/2-1 ))
T[2].append(click_graph( min(MAX_M[2]/4, MAX_N[2]) ))

print_tests(T)
