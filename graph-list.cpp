#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<vector<int>> l(n);
    while(true)
    {
        int u,v;
        cin>>u>>v;
        if(u==-1 && v==-1)
        {
            break;
        }
        l[u].push_back(v);
        l[v].push_back(u);


    }

    for (int i=0;i<n;i++) {
        cout <<i<<": ";
        for (int j=0;j<l[i].size(); j++) {
            cout<<l[i][j]<<" ";
        }
        cout<<"\n";
    }


    return 0;


}