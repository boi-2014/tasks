#include <iostream>
#include <fstream>
#include <set>
#include <sstream>

using namespace std;

const int MAX_N = 500000;

int N, M;
set<int> adj[MAX_N + 1];
bool visited[MAX_N + 1];

bool checkAndRemove(int u, int v) {
    if (adj[u].find(v) != adj[u].end()) {
        adj[u].erase(v);
        adj[v].erase(u);
        return true;
    }
    return false;
}

bool checkRoute(const string& route) {
    // cout << route << endl;
    stringstream s(route);

    int start;
    s >> start;

    set<int> used;
    used.insert(start);

    int u, v;
    for (u = start; !s.eof(); u = v) {
        s >> v;

        if (used.find(v) != used.end()) {
            cerr << "Same edge appears twice in a route " << v << endl;
            return false;
        }
        used.insert(v);

        if (!checkAndRemove(u, v)) {
            cerr << "Edge does not exist or used " << u << ", " << v << endl;
            return false;
        }
    }

    if (!checkAndRemove(start, v)) {
        cerr << "Edge does not exist or used " << start << ", " << v << endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    ifstream fi(argv[1]);
    ifstream fo(argv[3]);

    fi >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v;
        fi >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    string line;
    getline(fo, line);
    while (line != "") {
        if (!checkRoute(line)) {
            cerr << "Invalid route: " << line << endl;
            cout << "0" << endl;
            return 0;
        }
        getline(fo, line);
    }

    for (int i = 0; i < N; i++) {
        if (!adj[i].empty()) {
            cerr << "Some edges were not used" << endl;
            cout << "0" << endl;
            return 0;
        }
    }

    cout << "1" << endl;
    return 0;
}
