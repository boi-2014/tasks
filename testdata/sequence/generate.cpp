#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

const char *TESTS_DIR = "tests/";

const int SUBTASKS_COUNT = 5;

const int GROUP_A_NR = 2;
const int GROUP_A_MAX_K = 1000;
const int GROUP_A_MAX_N = 1000;

const int GROUP_B_NR = 4;
const int GROUP_B_MAX_K = 100000;



const int sample_test[] = { 7, 8, 9, 5, 1, 2 };
const int static_test[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };



using namespace std;

class Test {
public:
	int answer;

	Test() {
		answer = -1;
	}

	Test(const int s[]) {
		Test();
		int length = sizeof(s) / sizeof(*s);
		sequence.reserve(length);
		for (int i = 0; i < length; ++i)
			add(s[i]);
	}

	void add(int element) {
		if (element < 0 || element > 9)
			throw "Number with multiple digits in sequence element.";
		sequence.push_back(element);
	}

	bool hasAnswer() {
		return answer != -1;
	}

	int getK() {
		return sequence.size();
	}

	string getSequence() {
		string s = "";
		for (int i = 0; i < sequence.size(); ++i) {
			if (i)
				s += " ";
			s += char(sequence[i] + '0');
		}
		s += "\n";
		return s;
	}

private:
	vector<int> sequence;
};

void makeTestFile(string filename, Test test) {
	FILE *file = fopen(filename.c_str(), "w");
	if (file == NULL)
		throw "Failed to open file for writing.";
	fprintf(file, "%d\n", test.getK());
	fprintf(file, "%s", test.getSequence().c_str());
	fclose(file);
}

string toString(int number) {
	string s = "";
	while (number) {
		int digit = number % 10;
		s = char(digit + '0') + s;
		number /= 10;
	}
	return s;
}

Test generateRandomTest(const int MAX_K, const int MAX_N=-1) {
	Test test;
	int k = rand() % MAX_K;
	int n = rand();
	if (MAX_N != -1)
		n %= MAX_N;
	for (int i = 0; i < k; ++i) {
		string s = toString(n + i);
		int digit = s[rand() % s.length()] - '0';
		test.add(digit);
	}
	return test;
}

Test makeStaticTest(const int sequence[], int answer=-1) {
	Test test(sequence);
	test.answer = answer;
	return test;
}

vector<Test> tests[SUBTASKS_COUNT];

void addTest(int subtask, Test test) {
	tests[subtask].push_back(test);
}

int main() {
	try {
		//generate tests
		addTest(0, makeStaticTest(sample_test));
		for (int i = 0; i < 10; ++i)
			addTest(GROUP_A_NR, generateRandomTest(GROUP_A_MAX_K, GROUP_A_MAX_N));
		for (int i = 0; i < 10; ++i)
			addTest(GROUP_B_NR, generateRandomTest(GROUP_B_MAX_K));


		//get answers from solution


		//make tests
		for (int i = 0; i < SUBTASKS_COUNT; ++i) {
			for (int j = 0; j < tests[i].size(); ++j) {
				char buffer[255];
				sprintf(buffer, "%ssequence.%d-%02d", TESTS_DIR, i, j);
				string filename = buffer;
				cout << filename.c_str() << endl;
				makeTestFile(filename + ".in", tests[i][j]);

			}
		}
	}
	catch (const char *text) {
		cout << "Error: " << text << endl;
	}
	return 0;
}
