#include <iostream>
#include <vector>

using namespace std;



int main() {
    const int INF = 1e8;

    int n, m, L;
    while (cin >> n >> m >> L) {
        vector<int> a(m), b(m), s(m);
        vector<vector<int>> dist(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++)
            dist[i][i] = 0;

        for (int i = 0; i < m; i++) {
            cin >> a[i] >> b[i] >> s[i];
            a[i]--;
            b[i]--;
            if (s[i] < dist[a[i]][b[i]]) {
                dist[a[i]][b[i]] = s[i];
                dist[b[i]][a[i]] = s[i];
            }
        }




        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];

        long long base_cost = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                base_cost += (dist[i][j] >= INF ? L : dist[i][j]);

        long long max_cost = base_cost;


        for (int rem = 0; rem < m; rem++) {
            vector<vector<int>> g(n, vector<int>(n, INF));
            for (int i = 0; i < n; i++)
                g[i][i] = 0;

            for (int i = 0; i < m; i++) {
                if (i == rem) continue;
                if (s[i] < g[a[i]][b[i]]) {
                    g[a[i]][b[i]] = s[i];
                    g[b[i]][a[i]] = s[i];
                }
            }

            for (int k = 0; k < n; k++)
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        if (g[i][k] + g[k][j] < g[i][j])
                            g[i][j] = g[i][k] + g[k][j];

            long long cost = 0;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    cost += (g[i][j] >= INF ? L : g[i][j]);

            if (cost > max_cost)
                max_cost = cost;
        }

        cout << base_cost << " " << max_cost << "\n";
    }
    return 0;
}
