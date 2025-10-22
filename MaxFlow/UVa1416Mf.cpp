#include <iostream>
#include <vector>
#include <queue>
using namespace std;



struct Edge {
    int to, rev;
    int cap;
};

class Dinic {
public:
    const int INF = 1e9;
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    int n;

    Dinic(int n): n(n), graph(n), level(n), iter(n) {}

    void add_edge(int from, int to, int cap) {
        graph[from].push_back({to, static_cast<int>(graph[to].size()), cap});
        graph[to].push_back({from, static_cast<int>(graph[from].size())-1, 0});
    }

    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : graph[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < static_cast<int>(graph[v].size()); i++) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) break;
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    int n, m, L;
    while (cin >> n >> m >> L) {
        vector<int> a(m), b(m), s(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i] >> b[i] >> s[i];
            a[i]--; b[i]--;
        }
        int source = 0, sink = n - 1;
        Dinic dinic(n);
        for (int i = 0; i < m; i++) {
            dinic.add_edge(a[i], b[i], s[i]);
            dinic.add_edge(b[i], a[i], s[i]);
        }

        int base_flow = dinic.max_flow(source, sink);

        int min_flow_after_removal = base_flow;
        int critical_edge = -1;

        for (int rem = 0; rem < m; rem++) {
            Dinic dinic2(n);
            for (int i = 0; i < m; i++) {
                if (i == rem) continue;
                dinic2.add_edge(a[i], b[i], s[i]);
                dinic2.add_edge(b[i], a[i], s[i]);
            }
            int flow = dinic2.max_flow(source, sink);
            if (flow < min_flow_after_removal) {
                min_flow_after_removal = flow;
                critical_edge = rem;
            }
        }

        cout << "Max flow " << base_flow << "\n";
        cout << "Min max flow " << critical_edge + 1 << ": " << min_flow_after_removal << "\n";
        cout << "rebroto: (" << a[critical_edge] + 1 << ", " << b[critical_edge] + 1 << "), kapacitet: " << s[critical_edge] << "\n";
    }
    return 0;
}
