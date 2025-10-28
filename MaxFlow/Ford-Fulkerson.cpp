#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int to, rev;
    int cap;
};

class FordFulkerson {
public:
    const int INF = 1e9;
    int n;
    vector<vector<Edge>> graph;
    vector<bool> visited;

    FordFulkerson(int n): n(n), graph(n), visited(n) {}

    void add_edge(int from, int to, int cap) {
        graph[from].push_back({to, static_cast<int>(graph[to].size()), cap});
        graph[to].push_back({from, static_cast<int>(graph[from].size())-1, 0});
    }

    int dfs(int v, int t, int f, vector<int>& path) {
        if (v == t) {
            path.push_back(t);
            return f;
        }
        visited[v] = true;
        for (auto &e : graph[v]) {
            if (!visited[e.to] && e.cap > 0) {
                int pushed = dfs(e.to, t, min(f, e.cap), path);
                if (pushed > 0) {
                    e.cap -= pushed;
                    graph[e.to][e.rev].cap += pushed;
                    path.push_back(v);
                    return pushed;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (true) {
            fill(visited.begin(), visited.end(), false);
            vector<int> path;
            int pushed = dfs(s, t, INF, path);
            if (pushed == 0) break;

            flow += pushed;
            reverse(path.begin(), path.end());

            cout << "flow " << pushed << ": ";
            for (size_t i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i + 1 != path.size()) cout << " -> ";
            }
            cout << "\n";
        }
        return flow;
    }
};

int main() {

    // CP4 8.11
    int n= 4;
    FordFulkerson ff(n);

    ff.add_edge(0, 1, 8 );
    ff.add_edge(0, 2, 8 );
    ff.add_edge(2, 1, 1 );
    ff.add_edge(2, 3, 8 );
    ff.add_edge(1, 3, 8 );


    /*CP4 Ex Correct
    int n= 8;
    FordFulkerson ff(n);

    ff.add_edge(0, 1, 1 );
    ff.add_edge(0, 2, 1 );
    ff.add_edge(0, 3, 1 );
    ff.add_edge(1, 4, 1 );
    ff.add_edge(1, 5, 1 );
    ff.add_edge(1, 6, 1 );
    ff.add_edge(2, 5, 1 );
    ff.add_edge(3, 5, 1 );
    ff.add_edge(4, 7, 1 );
    ff.add_edge(5, 7, 1 );
    ff.add_edge(6, 7, 1 );
    */
    /*CP4 8.17.A
    int n= 5;
    FordFulkerson ff(n);

    ff.add_edge(0, 2, 5 );
    ff.add_edge(0, 3, 3 );
    ff.add_edge(1, 4, 99);
    ff.add_edge(2, 3, 2 );
    ff.add_edge(2, 1, 3);
    ff.add_edge(2, 4, 99);
    ff.add_edge(3, 1, 6);

    */
    /*CP4 8.17.B
    int n= 5;
    FordFulkerson ff(n);

    ff.add_edge(0, 2, 99);
    ff.add_edge(0, 3, 99 );
    ff.add_edge(1, 4, 4);
    ff.add_edge(2, 3, 2 );
    ff.add_edge(2, 1, 3);
    ff.add_edge(2, 4, 3);
    ff.add_edge(3, 1, 6);

    */
    /*CP4 8.17.C
    int n= 5;
    FordFulkerson ff(n);

    ff.add_edge(0, 2, 99);
    ff.add_edge(0, 3, 3);
    ff.add_edge(2, 3, 2);
    ff.add_edge(2, 1, 3 );
    ff.add_edge(2, 4, 3);
    ff.add_edge(1, 4, 99);
    ff.add_edge(3, 1, 6);

    */


    int source = 0, sink = n-1;

    int maxflow = ff.max_flow(source, sink);
    cout << maxflow << "\n";

    return 0;
}
