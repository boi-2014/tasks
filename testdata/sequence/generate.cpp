#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MAX_ANSWER = 102345678900000LL;


const char *TEMP_OUTPUT = "temp_output";//TODO: remove this file after

const char *SOLUTIONS_ROOT = "../../../solutions/sequence/";
const int SOLUTIONS_COUNT = 2;
const char *SOLUTIONS[SOLUTIONS_COUNT] = {
	"sequence_OK_Rihards",
	"sequence-daumilas",
	//"sequence_K2_Rihards",
	//"sequence-bruteforce-donatas",
	//"sequence-donatas",
	//"sequence-KlogK-vytautas",
};

const int SUBTASK_TEST_COUNT = 10;

const int FIRST_TEST_INDEX = 13;

class Test;

vector<Test*> tests;
int testIndex = FIRST_TEST_INDEX;

class Test {
public:
	vector<int> sequence;
	ll answer;

	Test() {
		answer = -1;
		tests.push_back(this);
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
	ll k = (rand() % maxK) + 1;
	ll n = (rand() % maxN) + 1;
	return generateTest(k, n);
}

Test generateSequenceTest(const ll k) {
	Test test;
	for (int i = 0; i < k; ++i) {
		test.add(rand() % 10);
	}
	return test;
}

Test generateRandomSequenceTest(const ll maxK) {
	return generateSequenceTest((rand() % maxK) + 1);
}

Test generateOneDigitRandomTest(const ll MAX_K) {
	Test test;
	int digit = rand() % 10;
	int k = (rand() % MAX_K) + 1;
	cout << k << " x \"" << digit << "\"" << endl;
	for (int i = 0; i < k; ++i) {
		test.add(digit);
	}
	return test;
}

//void foo(vector<int> )

//AAAA random(exluding BCD...) AAAA
Test generateaabaaTest(int length) {
	Test test;
	int sideValue = rand() % 10;
	int sidesSize = length / 3;
	int middleSize = length - (2 * sidesSize);
	int excludedCharactersCount = 3;

	vector<int> digits;
	for (int i = 0; i < 10; ++i) {
		digits.push_back(i);
	}

	for (int i = 0; i < excludedCharactersCount; ++i) {
		digits.erase(digits.begin() + (rand() % digits.size()));
	}

	for (int i = 0; i < sidesSize; ++i) {
		test.add(sideValue);
	}

	for (int i = 0; i < middleSize; ++i) {
		test.add(digits[rand() % digits.size()]);
	}

	for (int i = 0; i < sidesSize; ++i) {
		test.add(sideValue);
	}
	return test;
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
			cout << answer+i << " does not contain " << test.sequence[i] << endl;
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

void makeTest(string subtasks, Test test) {
	cout << "--------------" << endl;
	char buffer[255];
	sprintf(buffer, "sequence.%02d-%s", testIndex++, subtasks.c_str());
	string inputFile = string(buffer) + ".in";
	string outputFile = string(buffer) + ".sol";
	cout << "Supposed answer: " << test.answer << endl;
	cout << inputFile << endl;
	makeTestFile(inputFile, test);

	cout << outputFile << endl;
	ll answer = testFile(inputFile.c_str(), test);
	writeAnswer(answer, outputFile.c_str());
}

int main() {
	srand(time(0));
	try {
		cout << "Generating tests..." << endl;
		//generate tests
		//makeTest("0", generateSequenceTest(10000));

		makeTest("24", generateaabaaTest(1000));//TODO: manually check, if it can be made for subtask 1

		//#1: N, K <= 1000
		//for (int i = 0; i < 10; ++i)
			//makeTest("124", generateRandomTest(1000, 1000));
		for (int i = 0; i < 3; ++i)
			makeTest("12", generateTest(1000, 1000));

		//#2: K <= 1000
		for (int i = 0; i < 10; ++i)
			//makeTest("24", generateRandomTest(1000));
			makeTest("24", generateRandomSequenceTest(1000));
		for (int i = 0; i < 3; ++i)
			makeTest("24", generateSequenceTest(1000));

		//#3: all digits are equal
		for (int i = 0; i < 10; ++i)
			makeTest("3", generateOneDigitRandomTest(1000));

		//#4: K <= 100 000
		//for (int i = 0; i < 10; ++i)
			//makeTest("4", generateRandomTest(100000));
		//makeTest

	}
	catch (const char *text) {
		cout << "Error: " << text << endl;
	}
	return 0;
}
