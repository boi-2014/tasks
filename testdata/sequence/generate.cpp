#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MAX_ANSWER = 102345678900000LL;


const char *TEMP_OUTPUT = "temp_output";//TODO: remove this file after

const char *SOLUTIONS_ROOT = "../../solutions/sequence/";
const int SOLUTIONS_COUNT = 3;
const char *SOLUTIONS[SOLUTIONS_COUNT] = {
	"sequence_OK_Rihards",
	"sequence-daumilas",
	"sequence-bruteforce-donatas",
	//"sequence-donatas",
	//"sequence-KlogK-vytautas",
};

const int SUBTASK_TEST_COUNT = 10;

const int SUBTASK_START_NUMBER[SOLUTIONS_COUNT] = {
	0,
	0,
	0,
};

const int SUBTASKS_COUNT = 5;


class Test {
public:
	vector<int> sequence;
	ll answer;

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


//TODO: remove
const int sample_test[] = { 7, 8, 9, 5, 1, 2 };
const int static_test[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };


vector<Test> tests[SUBTASKS_COUNT];


void makeTestFile(string filename, Test test) {
	FILE *file = fopen(filename.c_str(), "w");
	if (file == NULL)
		throw "Failed to open file for writing.";
	fprintf(file, "%d\n", (int)test.sequence.size());
	fprintf(file, "%s", test.getSequence().c_str());
	fclose(file);
}

string toString(ll number) {
	string s = "";
	while (number) {
		int digit = number % 10;
		s = char(digit + '0') + s;
		number /= 10;
	}
	return s;
}

Test generateTest(const ll k, const ll n) {
	Test test;
	for (int i = 0; i < k; ++i) {
		string s = toString(n + i);
		int digit = s[rand() % s.length()] - '0';
		test.add(digit);
	}
	test.answer = n;
	return test;

}

Test generateRandomTest(const ll maxK, const ll maxN=MAX_ANSWER) {
	ll k = rand() % (maxK+1);
	ll n = rand() % (maxN+1);
	return generateTest(k, n);
}

Test generateOneDigitRandomTest(const ll MAX_K) {
	Test test;
	int digit = rand() % 10;
	int k = rand() % (MAX_K + 1);
	cout << k << " x \"" << digit << "\"" << endl;
	for (int i = 0; i < k; ++i) {
		test.add(digit);
	}
	return test;
}

Test makeStaticTest(const int sequence[], int answer=-1) {
	Test test(sequence);
	test.answer = answer;
	return test;
}


void addTest(int subtask, Test test) {
	tests[subtask-1].push_back(test);
}

ll readAnswer(const char *filename) {
	ll answer;
	FILE *file = fopen(filename, "r");
	fscanf(file, "%lld", &answer);
	fclose(file);
	return answer;
}

void writeAnswer(ll answer, const char *filename) {
	FILE *file = fopen(filename, "w");
	fprintf(file, "%lld\n", answer);
	fclose(file);
}

bool contains(ll number, int digit) {
	while (number != 0) {
		if (number % 10 == digit)
			return true;
		number /= 10;
	}
	return false;
}

//if answer is possible (not necessary smallest)
bool isCorrect(Test test, ll answer) {
	for (ll i = 0; i < test.sequence.size(); ++i) {
		if (!contains(answer + i, test.sequence[i])) {
			return false;
		}
	}
	return true;
}

ll testFile(const char *inputFilename, Test test) {
	char command[1024];
	ll answer = test.answer;
	for (int k = 0; k < SOLUTIONS_COUNT; ++k) {
		string solution = string(SOLUTIONS_ROOT) + string(SOLUTIONS[k]);
		sprintf(command, "%s < %s > %s", solution.c_str(), inputFilename, TEMP_OUTPUT);
		system(command);
		ll now = readAnswer(TEMP_OUTPUT);
		bool correct;
		if (answer != -1 && now == answer) {
			//the same answer
			correct = true;
		}
		else if (answer == -1 || (answer != -1 && now < answer)) {
			//check if new better answer is correct
			correct = isCorrect(test, now);
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
	return answer;
}

int main() {
	srand(time(0));
	try {
		cout << "Generating tests..." << endl;
		//generate tests
		//#1: N, K <= 1000
		for (int i = 0; i < SUBTASKS_COUNT - SUBTASK_START_NUMBER[0]; ++i)
			addTest(1, generateRandomTest(1000, 1000));
		//#2: K <= 1000
		for (int i = 0; i < SUBTASKS_COUNT - SUBTASK_START_NUMBER[1]; ++i)
			addTest(2, generateRandomTest(1000));
		//#3: all digits are equal
		for (int i = 0; i < SUBTASKS_COUNT - SUBTASK_START_NUMBER[2]; ++i)
			addTest(1, generateOneDigitRandomTest(1000));
		//#4: K <= 100 000
		for (int i = 0; i < 10; ++i)
			addTest(4, generateRandomTest(100000));

		//make tests
		for (int i = 0; i < SUBTASKS_COUNT; ++i) {
			for (int j = 0; j < tests[i].size(); ++j) {
				cout << "--------------" << endl;
				char buffer[255];
				sprintf(buffer, "sequence.%d-%02d", i+1, SUBTASK_START_NUMBER[i]+j);
				string inputFile = string(buffer) + ".in";
				string outputFile = string(buffer) + ".sol";
				cout << "Supposed answer: " << tests[i][j].answer << endl;
				cout << inputFile << endl;
				makeTestFile(inputFile, tests[i][j]);

				cout << outputFile << endl;
				ll answer = testFile(inputFile.c_str(), tests[i][j]);
				writeAnswer(answer, outputFile.c_str());
			}
		}
	}
	catch (const char *text) {
		cout << "Error: " << text << endl;
	}
	return 0;
}
