import re, glob

pattern = re.compile(r'^sequence\.(\d{2})p?-(\d+)\.in$')

def read_solution(filename):
	print filename
	f = open(filename)
	n = int(f.readline())
	return n

def read_input(filename):
	f = open(filename)
	k = int(f.readline())
	values = f.readline().split()
	f.close()
	return k, values

def all_equal(values):
	value = values[0]
	for cur in values[1:]:
		if value != cur:
			raise ValueError

def validate_file(inputFilename, subtasks):
	n = read_solution(inputFilename[:-2] + 'sol')
	assert n > 0
	k, b = read_input(inputFilename)
	assert k == len(b)
	assert 0 < k <= 100000
	for subtask in subtasks:
		if subtask == 1:
			assert k <= 1000
			assert n <= 1000
		elif subtask == 2:
			assert k <= 1000
		elif subtask == 3:
			#TODO
			all_equal(b)

		elif subtask == 4:
			pass
		else:
			raise ValueError

for filename in sorted(glob.glob('sequence.*.in')):
	matches = pattern.match(filename)
	assert matches
	subtasks = [int(a) for a in matches.group(2)]
	validate_file(filename, subtasks)
