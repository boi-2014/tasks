#include <compframework.h>
#include<cstdio>
#include<cstdlib>
#include<set>
#include<vector>

using namespace std;
typedef pair<int, int> edge;

set<edge> input;
set<edge> traversed;
vector<vector<int> > user_output;
int num_nodes;

inline pair<int, int> make_edge(int u, int v)
{
	return make_pair(min(u, v), max(u, v));
}

void load_input()
{
	int n, m;
	fscanf(fin, "%d %d", &n, &m);
	num_nodes = n;

	for(int i = 0; i < m; ++i)
	{
		int u, v;
		fscanf(fin, "%d %d", &u, &v);
		input.insert(make_edge(u, v));
	}
}

// FIXME There are several holes in here...
// For example, integers from user output are sometimes not checked to be in the allowed range.

void load_user_output()
{
	int cycles;
    try { cycles = read_or_fail<int>(fout); }
    catch(string s) { result(0.0, "Not correct: no integer in file"); }

	for(int i = 0; i < cycles; ++i)
	{
		int count;
        try { count = read_or_fail<int>(fout); }
        catch(string s) { result(0.0, "Not correct: no integer in file"); }

		user_output.push_back(vector<int>(count));

		for(int j = 0; j < count; ++j)
		{
            try { user_output.back()[j] = read_or_fail<int>(fout); }
            catch(string s) { result(0.0, "Not correct: no integer in file"); }
		}
	}
}

edge find_missing()
{
	for(set<edge>::iterator i = input.begin(); i != input.end(); ++i)
		if(traversed.find(*i) == traversed.end())	return *i;
}

void check() {
    load_input();
    load_user_output();

    for(int i = 0; i < (int)user_output.size(); ++i)
    {
        //printf("%d. Zyklus... ", i + 1);

        if(user_output[i].size() < 2)
            result(0.0, "Wrong output. No edges on \"cycle\".");

        int u, v = user_output[i][0];

        if(v < 1 || v > num_nodes)
            result(0.0, "Wrong output. Node %d does not appear in input.", v);

        for(int j = 1; j < (int)user_output[i].size(); ++j)
        {
            u = v;
            v = user_output[i][j];

            if(v < 1 || v > num_nodes)
                result(0.0, "Wrong output. Node %d does not appear in input.", v);

            edge e = make_edge(u, v);

            if(input.find(e) == input.end())
                result(0.0, "Wrong output. Edge %d--%d is not in input.", u, v);

            if(traversed.find(e) != traversed.end())
                result(0.0, "Wrong output. Edge %d--%d contained in at least two cycles.", u, v);

            traversed.insert(e);
        }

        //if(user_output[i].back() != user_output[i][0])
        //    result(0.0, "Wrong Output. At least one tour isn't a cycle (did you forget the last node?).");

        //printf("korrekt.");
    }

    if(traversed.size() != input.size())
    {
        edge e = find_missing();
        result(0.0, "Wrong output. Street %d--%d not served.", e.first, e.second);
    }

    result(1.0, "Correct");
}
