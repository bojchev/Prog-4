#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
    int from, to, w;
};

int main()
{
    int n, e, s;
    cin >> n >> e >> s;
    vector<Edge> list(e);

    for (int i = 0; i < e; ++i)
    {
        cin >> list[i].from >> list[i].to >> list[i].w;
    }

    vector<int> dist(n, (int)1e9);
    dist[s] = 0;

    for (int rep = 0; rep < n - 1; ++rep)
    {
        for (int i = 0; i < e; ++i)
        {
            if (dist[list[i].from] < (int)1e9 && dist[list[i].from] + list[i].w < dist[list[i].to])
            {
                dist[list[i].to] = dist[list[i].from] + list[i].w;
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        cout << (dist[i] == (int)1e9 ? -1 : dist[i]) << " ";
    }
}
