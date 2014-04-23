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

def find_cycle (N, adj, k):
	visited = [0 for i in range (N + 1)]
	v = random.randint (1, N);
	while (len(k[v]) == 0):
		v = random.randint(1, N);
	cycle = [v]
	edges = []
	p = -1
	while (True):
		#print "V = %d" % v, cycle
		visited[v] = True
		neigh = list(k[v])
		random.shuffle(neigh)
		if (len(neigh)==0):
			return False
		for j in neigh:
			u = getU(v, adj[j])
			if (p != u):
				edges.append(j)
				#print "rm %d->%d (%d)" % (v, u, j), adj[j]
				k[u].remove(j)
				k[v].remove(j)
				if not visited[u]:
					cycle.append(u)
					v = u
					p = v
					break
				else:
					ans = []
					ans = cycle[cycle.index(u):]
					#print ans
					for x in range(len(cycle)-len(ans)):
						k[cycle[x]].add(edges[x])
						k[cycle[x+1]].add(edges[x])
						#print cycle[x], cycle[x+1], edges[x]
					return (ans, k)
	return False

def rand_small_graph (N, M):
	dict = {}

	
	adj = []
	k = [set() for x in range (N+1)]
	
	index = 0
	for i in range (1, N +1):
		for j in range (i+1, N+1):
			adj.append((i, j));
			k[i].add(index)
			k[j].add(index)
			index += 1	
	print "VIso briaunu: %d" % len(adj)	
	adj_ret = []

	b = find_cycle(N, adj, k)
	while (b != False and len(adj_ret) < M):
		k = b[1]
		#print "lenret = %d, lenAll = %d, M = %d" % (len(b[0]), len(adj_ret), M)
		if (len(b[0]) + len(adj_ret) > M):
			print "Rand graph small N = %d, M = %d" % (N, len(adj_ret))
			return (N, len(adj_ret), adj_ret)
		
		for i in range(len(b[0])):
			adj_ret.append((b[0][i], b[0][(i+1)%len(b[0])]))
		
		b = find_cycle(N, adj, k)
	
	print "Rand graph small N = %d, M = %d" % (N, len(adj_ret))
	return (N, len(adj_ret), adj_ret)	

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


def print_test (T, filename):
	file = open(filename, "w")
	file.write(str(T[0]) + " " + str(T[1]) + "\n")
	for p in T[2]:
		file.write(str(p[0]) + " " + str(p[1]) + "\n")
	file.close()


def print_tests(T):
	template = "senior.%d-%02d%s.in"
	T[1] = T[0] + T[1]
	T[2] = T[0] + T[2]
	for subtask, t in enumerate(T):
		print "Printing %d subtask:" % (subtask+1)
		for tnr, test in enumerate(t):
			#print "Printing test %d" % tnr
			filename = template % (subtask+1, tnr+1, ("","p")[subtask==0 and tnr==0])
			file = open(filename, "w")
			file.write(str(test[0]) + " " + str(test[1]) + "\n")
			random.shuffle(test[2])
			for edge in test[2]:
				file.write(str(edge[0]) + " " + str(edge[1]) + "\n")
			file.close()


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

#1->(2,3,..,K+1), 2->(3,4,..,K+2)
T[0].append(dense_small_graph(MAX_N[0], MAX_M[0]))


print "\nGENERATING SUBTASK 2:"

T[1].append(ring(MAX_N[1]))
T[1].append(ring_of_rings(MAX_N[1]/4))
T[1].append(paths_len3(MAX_M[1]*2/3 + 1))
T[1].append(dense_small_graph(MAX_N[1], MAX_M[1]))

print "\nGENERATING SUBTASK 3:"

T[2].append(ring(MAX_N[2]))
T[2].append(ring_of_rings(MAX_N[2]/4))
T[2].append(paths_len3(MAX_M[2]*2/3 +1))
T[2].append(dense_small_graph(MAX_N[2], MAX_M[2]))

print_tests(T)
