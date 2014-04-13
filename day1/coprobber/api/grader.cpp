#include <cstdio>
#include <utility>
#include "coprobber.h"

using namespace std;

static const bool TRACK_CALLS = false;

static int N, CopCanWin;
static bool A[MAX_N][MAX_N];

// Where should the robber go if the first index is the cop's
// position and the second index is the robber's position?
// RS[c][N] stores robber's starting corners.
static int RobberStrategy[MAX_N][MAX_N + 1];

// Visited positions are stored in the following array
static bool VisitedPositions[MAX_N][MAX_N];

typedef pair<bool, const char*> GraderResult;

GraderResult runGrader() {
	int copCorner = start(N, A);
	if (TRACK_CALLS)
		fprintf(stderr, "start() = %d\n", copCorner);
	
	if ((copCorner != -1) && !CopCanWin)
		return GraderResult(false, "Cop cannot catch the robber, but start() did not return -1");
	if ((copCorner == -1) && CopCanWin)
		return GraderResult(false, "Cop can catch the robber, but start() returned -1");
	if (!CopCanWin)
		return GraderResult(true, NULL);
	if (copCorner < 0 || copCorner >= N)
		return GraderResult(false, "start() returned a value that is outside the 0..N-1 range");
	int robberCorner = RobberStrategy[copCorner][N];
	
	if (robberCorner == copCorner)  // If N = 1
		return GraderResult(true, NULL);
	
	while (true) {
		int nextCopCorner = nextMove(robberCorner);
		
		if (TRACK_CALLS)
			fprintf(stderr, "nextMove(%d) = %d\n", robberCorner, nextCopCorner);
		
		/**
		 * Check if the move is valid:
		 *   - the returned corner is within bounds
		 *   - the new corner is either the same or is a neighbour to the old one
		 */
		if (nextCopCorner < 0 || nextCopCorner >= N
				|| !(copCorner == nextCopCorner || A[copCorner][nextCopCorner]))
			return GraderResult(false,
						"nextMove() returned a value that is either outside 0..N-1 "
						"or the new cop position is not a neighbour to the previous one");
		copCorner = nextCopCorner;
		
		// Check if the same position has not been encountered before
		if (VisitedPositions[copCorner][robberCorner])
			return GraderResult(false, "the situation repeated");
		VisitedPositions[copCorner][robberCorner] = true;
		
		// Check the winning condition
		if (copCorner == robberCorner)
			return GraderResult(true, NULL);
		
		robberCorner = RobberStrategy[copCorner][robberCorner];
		
		// Moving to cop's position could have been the only
		// valid move for the robber
		if (copCorner == robberCorner)
			return GraderResult(true, NULL);
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &A[i][j]);
	
	scanf("%d", &CopCanWin);
	if (CopCanWin) {
		for (int c = 0; c < N; c++)
			for (int r = 0; r <= N; r++)
				scanf("%d", &RobberStrategy[c][r]);
	}
	
	GraderResult result = runGrader();
	puts(result.first ? "OK" : "WRONG");
	if (result.second != NULL)
		puts(result.second);
	
	return 0;
}
