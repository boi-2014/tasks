#include<cstdio>
#include<cstdlib>
#include<vector>

using namespace std;
typedef pair<int, int> pii;

void grid(int size)
{
	int running = 0, num_nodes = 0;
	vector<pii> edges;

	for(int i = 1; i <= size; ++i)
	{
		int off = size + 2 - i;

		for(int j = 1; j <= size + 1 - i; ++j)
		{
			++running;
			++num_nodes;

			if(j != size + 1 - i)	edges.push_back(pii(running, running + 1));

			if(i != 1)
			{
				edges.push_back(pii(running, running-off));
				edges.push_back(pii(running, running-off+1));
			}
		}
	}

	printf("%d %d\n", num_nodes, (int)edges.size());
	for(int i = 0; i < (int)edges.size(); ++i)	printf("%d %d\n", edges[i].first, edges[i].second);
}

int main(int argc, char ** argv)
{
	//freopen(argv[2], "w", stdout);

	int size;	sscanf(argv[1], "%d", &size);
	grid(size);
	return 0;
}
