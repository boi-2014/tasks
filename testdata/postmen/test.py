import glob, re, sys, subprocess, time, numpy
import matplotlib.pyplot as P

FN_PATTERN = re.compile(r'^senior\.(\d{2})p?-(.*)\.in$')

t1, t2 = [], []

def check_file(fn, test):
	print "TEST No ", test, ":"
	output = subprocess.call([sys.argv[1], "<" + fn, ">output"], shell=True)
	tt1, tt2 = [], []
	for xxx in xrange(3):
		time1 = time.clock()
		output1 = subprocess.check_output(["checker.exe", fn, "dummy", "output"], shell=True)
		time2 = time.clock()
		output1 = subprocess.check_output(["hchecker.exe", fn, "dummy", "output"], shell=True)
		time3 = time.clock()
		tt1.append(time2-time1)
		tt2.append(time3-time2)
	t1.append(sum(tt1)/len(tt1))
	t2.append(sum(tt2)/len(tt2))

if (len (sys.argv) < 2):
	print sys.argv
	print "Usage: test.py sol.exe"	
else:
	for fn in glob.glob('senior.*.in'):
		matches = FN_PATTERN.match(fn)
		check_file(fn, int(matches.group(1)))

P.plot(range(1, 27), t1, 'r-')
P.plot(range(1, 27), t2, 'b-')
P.axis([0, 28, 0.0, 2.0])
P.legend(("NlogM", "Hash"), loc = 'upper left')
P.show()
