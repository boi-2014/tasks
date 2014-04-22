#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

const char *TESTS_DIR = "";

const char *TEMP_OUTPUT = "temp_output";

const char *SOLUTIONS_ROOT = "../../solutions/sequence/";
const int SOLUTIONS_COUNT = 3;
const char *SOLUTIONS[SOLUTIONS_COUNT] = {
	"sequence-bruteforce-donatas",
	"sequence_OK_Rihards",
	"sequence-daumilas",
	//"sequence-donatas",
	//"sequence-KlogK-vytautas", //needs fixing
};

const int SUBTASKS_COUNT = 5;

const int GROUP_A_NR = 0;
const int GROUP_A_MAX_K = 1000;
const int GROUP_A_MAX_N = 1000;

const int GROUP_B_NR = 1;
const int GROUP_B_MAX_K = 100000;



const int sample_test[] = { 7, 8, 9, 5, 1, 2 };
const int static_test[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };



using namespace std;

class Test {
public:
	vector<int> sequence;
	long long answer;

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
};

void makeTestFile(string filename, Test test) {
	FILE *file = fopen(filename.c_str(), "w");
	if (file == NULL)
		throw "Failed to open file for writing.";
	fprintf(file, "%d\n", (int)test.sequence.size());
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

Test generateTest(const int k, const int n) {
	Test test;
	for (int i = 0; i < k; ++i) {
		string s = toString(n + i);
		int digit = s[rand() % s.length()] - '0';
		test.add(digit);
	}
	test.answer = n;
	return test;

}

Test generateRandomTest(const int MAX_K, const int MAX_N=-1) {
	int k = rand() % MAX_K;
	int n = rand();
	if (MAX_N != -1)
		n %= MAX_N;
	return generateTest(k, n);
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

long long readAnswer(const char *filename) {
	long long answer;
	FILE *file = fopen(filename, "r");
	fscanf(file, "%lld", &answer);
	fclose(file);
	return answer;
}

void writeAnswer(long long answer, const char *filename) {
	FILE *file = fopen(filename, "w");
	fprintf(file, "%lld\n", answer);
	fclose(file);
}

bool contains(long long number, int digit) {
	while (number != 0) {
		if (number % 10 == digit)
			return true;
		number /= 10;
	}
	return false;
}

//if answer is possible (not necessary smallest)
bool isCorrect(Test test, long long answer) {
	for (long long i = 0; i < test.sequence.size(); ++i) {
		if (!contains(answer + i, test.sequence[i])) {
			return false;
		}
	}
	return true;
}

int main() {
	try {
		cout << "Generating tests..." << endl;
		//generate tests
		//addTest(0, makeStaticTest(sample_test));
		//for (int i = 1; i < 1000; ++i) {
			//addTest(0, generateTest(100, i));
		//}
		for (int i = 0; i < 10; ++i)
			addTest(GROUP_A_NR, generateRandomTest(GROUP_A_MAX_K, GROUP_A_MAX_N));
		//for (int i = 0; i < 10; ++i)
			//addTest(GROUP_B_NR, generateRandomTest(GROUP_B_MAX_K));
		//for (int i = 1; i < 100; ++i)
			//addTest(0, generateTest(10, i));


		//make tests
		for (int i = 0; i < SUBTASKS_COUNT; ++i) {
			for (int j = 0; j < tests[i].size(); ++j) {
				cout << "--------------" << endl;
				char buffer[255];
				sprintf(buffer, "%ssequence.%d-%02d", TESTS_DIR, i, j);
				string inputFile = string(buffer) + ".in";
				string outputFile = string(buffer) + ".sol";
				cout << "Supposed answer: " << tests[i][j].answer << endl;
				cout << inputFile << endl;
				makeTestFile(inputFile, tests[i][j]);

				cout << outputFile << endl;
				char command[1024];
				long long answer = tests[i][j].answer;
				for (int k = 0; k < SOLUTIONS_COUNT; ++k) {
					string solution = string(SOLUTIONS_ROOT) + string(SOLUTIONS[k]);
					sprintf(command, "%s < %s > %s", solution.c_str(), inputFile.c_str(), TEMP_OUTPUT);
					system(command);
					long long now = readAnswer(TEMP_OUTPUT);
					bool correct;
					if (answer != -1 && now == answer) {
						//the same answer
						correct = true;
					}
					else if (answer == -1 || (answer != -1 && now < answer)) {
						//check if new better answer is correct
						correct = isCorrect(tests[i][j], now);
						if (correct)
							answer = now;
					} 
					cout << (correct ? "+" : "-") << now << " by " << SOLUTIONS[k] << endl;
					if (!correct)
						cout << "----------------------------------------------------------incorrect" << endl;
				}
				if (answer == -1) {
					cout << "No correct solution found" << endl;
					throw "No correct solution found";
				}
				cout << "Answer: " << answer << endl;
				writeAnswer(answer, outputFile.c_str());
			}
		}
	}
	catch (const char *text) {
		cout << "Error: " << text << endl;
	}
	return 0;
}
