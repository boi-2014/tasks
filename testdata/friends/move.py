

# k/friends.in.n
def read_test_case (k, n):
	file = open("%d/friends.in.%d" % (k, n))
	s1 = file.readline().replace('\n', '')
	file.close()
	file = open("%d/friends.out.%d" % (k, n))
	s2 = file.readline().replace('\n', '')
	file.close()	
	return (s1, s2)

templateI = "friends.%02d%s-%s.in"
templateO = "friends.%02d%s-%s.sol"


def print_tests ():
    
	K = 1

	for n in range(1, 43 + 1):
		s1, s2 = read_test_case(1, n)
		if K == 3 or K == 20 or K == 43:
			ss = "p"
		else:
			ss = ""
		file = open(templateI % (K, ss, "12"), "w")
		file.write(str(len(s1)) + "\n" + s1 + "\n")
		file.close()
		
		file = open(templateO % (K, ss, "12"), "w")
		file.write(s2 + "\n")
		file.close()
		K += 1
    
	for n in range (1, 11 + 1):
		s1, s2 = read_test_case(2, n)

		file = open(templateI % (K, "", "12"), "w")
		file.write(str(len(s1)) + "\n" + s1 + "\n")
		file.close()
		
		file = open(templateO % (K, "", "12"), "w")
		file.write(s2 + "\n")
		file.close()
		K += 1
    
	for n in range (1, 11 + 1):
		s1, s2 = read_test_case(3, n)

		file = open(templateI % (K, "", "2"), "w")
		file.write(str(len(s1)) + "\n" + s1 + "\n")
		file.close()
		
		file = open(templateO % (K, "", "2"), "w")
		file.write(s2 + "\n")
		file.close()
		K += 1



print_tests ()
