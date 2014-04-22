#include <cstdio>
#include <cstring>

int main(int argc, char *argv[]) {
	if (argc < 4) {
		fprintf(stderr, "Usage: checker file.in file.sol file.out\n");
		return 1;
	}
	
	int partialScoring;
	FILE *fsol = fopen(argv[2], "r");
	fscanf(fsol, "%d", &partialScoring);
	fclose(fsol);
	
	char result[9];
	FILE *fout = fopen(argv[3], "r");
	fscanf(fout, "%8s", result);
	fclose(fout);
	
	if (!strcmp(result, "OK"))
		printf("1\n");
	else if (!strcmp(result, "PARTFAIL") && partialScoring)
		printf("0.3\n");
	else
		printf("0\n");
	
	return 0;
}
