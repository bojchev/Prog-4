#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int to, rev;
    int cap;
};

class Dinic {
public:
    int n;
    vector<vector<Edge>> graph;
    vector<int> level, iter;

    Dinic(int n) : n(n), graph(n), level(n), iter(n) {}

    void add_edge(int from, int to, int cap) {
        graph[from].push_back({to, (int)graph[to].size(), cap});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto &e : graph[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int t, int f, vector<int> &path) {
        if (v == t) {
            path.push_back(t);
            return f;
        }
        for (int &i = iter[v]; i < (int)graph[v].size(); i++) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
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
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            vector<int> path;
            int pushed;
            while ((pushed = dfs(s, t, INT_MAX, path)) > 0) {
                flow += pushed;
                reverse(path.begin(), path.end());
                cout << "flow " << pushed << ": ";
                for (size_t i = 0; i < path.size(); i++) {
                    cout << path[i];
                    if (i + 1 != path.size()) cout << " -> ";
                }
                cout << "\n";
                path.clear();
            }
        }
        return flow;
    }
};

int main() {
    /*CP4 8.11
    int n= 4;
    Dinic d(n);

    d.add_edge(0, 1, 8 );
    d.add_edge(0, 2, 8 );
    d.add_edge(2, 1, 1 );
    d.add_edge(2, 3, 8 );
    d.add_edge(1, 3, 8 );
    */

    /*CP4 Ex Correct
    int n= 8;
    Dinic d(n);

    d.add_edge(0, 1, 1 );
    d.add_edge(0, 2, 1 );
    d.add_edge(0, 3, 1 );
    d.add_edge(1, 4, 1 );
    d.add_edge(1, 5, 1 );
    d.add_edge(1, 6, 1 );
    d.add_edge(2, 5, 1 );
    d.add_edge(3, 5, 1 );
    d.add_edge(4, 7, 1 );
    d.add_edge(5, 7, 1 );
    d.add_edge(6, 7, 1 );
    */
    /*CP4 8.17.A
    int n= 5;
    Dinic d(n);

    d.add_edge(0, 2, 5 );
    d.add_edge(0, 3, 3 );
    d.add_edge(1, 4, 99);
    d.add_edge(2, 3, 2 );
    d.add_edge(2, 1, 3);
    d.add_edge(2, 4, 99);
    d.add_edge(3, 1, 6);

    */
    /*CP4 8.17.B
    int n= 5;
    Dinic d(n);

    d.add_edge(0, 2, 99);
    d.add_edge(0, 3, 99 );
    d.add_edge(1, 4, 4);
    d.add_edge(2, 3, 2 );
    d.add_edge(2, 1, 3);
    d.add_edge(2, 4, 3);
    d.add_edge(3, 1, 6);

    */
    /*CP4 8.17.C
    int n= 5;
    Dinic d(n);

    d.add_edge(0, 2, 99);
    d.add_edge(0, 3, 3);
    d.add_edge(2, 3, 2);
    d.add_edge(2, 1, 3 );
    d.add_edge(2, 4, 3);
    d.add_edge(1, 4, 99);
    d.add_edge(3, 1, 6);

    */


    int source = 0, sink = n - 1;

    int maxflow = d.max_flow(source, sink);
    cout <<maxflow << "\n";

    return 0;
}
