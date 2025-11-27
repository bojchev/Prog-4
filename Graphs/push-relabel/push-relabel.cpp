#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

void pushFlow(int from, int to, vector<int>& h, vector<int>& excess, vector<vector<int>>& cap, vector<vector<int>>& flow, queue<int>& active)
{
    int d = min(excess[from], cap[from][to] - flow[from][to]);
    flow[from][to] += d;
    flow[to][from] -= d;
    excess[from] -= d;
    excess[to] += d;
    if (d && excess[to] == d)
    {
        active.push(to);
    }
}

void relabel(int u, int n, vector<int>& h, vector<int>& excess, vector<vector<int>>& cap, vector<vector<int>>& flow, queue<int>& active)
{
    int minHeight = INF;
    for (int v = 0; v < n; v++)
    {
        if (cap[u][v] - flow[u][v] > 0)
        {
            minHeight = min(minHeight, h[v]);
        }
    }
    if (minHeight != INF)
    {
        h[u] = minHeight + 1;
    }
}

void discharge(int u, int n, vector<int>& ptr, vector<int>& h, vector<int>& excess, vector<vector<int>>& cap, vector<vector<int>>& flow, queue<int>& active)
{
    while (excess[u] > 0)
    {
        if (ptr[u] < n)
        {
            int v = ptr[u];
            if (cap[u][v] - flow[u][v] > 0 && h[u] > h[v])
            {
                pushFlow(u, v, h, excess, cap, flow, active);
            }
            else
            {
                ptr[u]++;
            }
        }
        else
        {
            relabel(u, n, h, excess, cap, flow, active);
            ptr[u] = 0;
        }
    }
}

int maxFlow(int src, int sink, int n, vector<int>& ptr, vector<int>& h, vector<int>& excess, vector<vector<int>>& cap, vector<vector<int>>& flow, queue<int>& active)
{
    h.assign(n, 0);
    h[src] = n;
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);
    excess[src] = INF;

    for (int i = 0; i < n; i++)
    {
        if (i != src)
        {
            pushFlow(src, i, h, excess, cap, flow, active);
        }
    }
    ptr.assign(n, 0);

    while (!active.empty())
    {
        int curr = active.front();
        active.pop();
        if (curr != src && curr != sink)
        {
            discharge(curr, n, ptr, h, excess, cap, flow, active);
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++)
    {
        result += flow[i][sink];
    }
    return result;
}

int main()
{
    int n, edges;
    cin >> n >> edges;
    vector<vector<int>> cap, flow;
    vector<int> h, excess, ptr;
    queue<int> active;
    cap.assign(n, vector<int>(n, 0));
    for (int i = 0; i < edges; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        cap[u][v] = w;
    }
    int src, sink;
    cin >> src >> sink;
    int ans = maxFlow(src, sink, n, ptr, h, excess, cap, flow, active);
    cout << ans << '\n';
    return 0;
}