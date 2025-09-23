#include<iostream>
#include<vector>
#include<tuple>
using namespace std;

int main(){
    int max=1e9, v, e;
    cin>>v>> e;

    vector<tuple<int, int, int>> edges;

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin>>u>>v>>w;
        edges.push_back(make_tuple(u, v, w));
    }


    vector<vector<int>> m(v, vector<int>(v, max));


    for (int i = 0; i < v; i++) {
        m[i][i] = 0;
    }


    for (size_t i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int w = get<2>(edges[i]);
        m[u][v] = w;
    }


    for (int k = 0; k < v; k++) {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (m[i][k] != max && m[k][j] != max) {
                    m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
                }
            }
        }
    }


    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (m[i][j] == max) cout << "INF ";
            else cout << m[i][j] << " ";
        }
        cout << "\n";
    }
}