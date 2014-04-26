#include <cstdio>
#include <cstring>

int main(int argc, char *argv[]) {
	if (argc < 4) {
		fprintf(stderr, "Usage: checker file.in file.sol file.out\n");
		return 1;
	}
	
	char result[9];
	FILE *fout = fopen(argv[3], "r");
	fscanf(fout, "%8s", result);
	fclose(fout);
	
	if (!strcmp(result, "OK")) {
		printf("1\n");
		fprintf(stderr, "Correct\n");
	} else if (!strcmp(result, "PARTFAIL")) {
		printf("0.3\n");
		fprintf(stderr, "nextMove() failed - you will get 30%% points for this test\n");
	} else {
		printf("0\n");
		fprintf(stderr, "Incorrect\n");
	}
	return 0;
}
