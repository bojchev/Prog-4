#include <iostream>
#include <vector>

using namespace std;


int main() {


    int n;
    cin >> n;
    vector<vector<int>> m(n, vector<int>(n, 0));
    int u, v;
    while (true){
        cin >> u >> v;
        if (u==-1 && v==-1)
        {
            break;
        }
        u--;
        v--;
        if (u >= 0 && u < n && v >= 0 && v < n) {
            m[u][v] = 1;
            m[v][u] = 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << m[i][j] << (j + 1 == n ? '\n' : ' ');
    }

    return 0;
}