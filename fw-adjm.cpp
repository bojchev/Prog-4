#include <iostream>

using namespace std;

int main(){

    int max=1e9, v;
    cin>>v;
    vector<vector<int>>m(v,vector<int>(v,max));

    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            cin>>m[i][j];
        }
    }
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            for(int k=0;k<v;k++)
            {
                if(m[j][i]!=max&&m[i][k]!=max)
                {
                    m[j][k]=min(m[j][k],m[j][i]+m[i][k]);
                }
            }
        }
    }
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            cout<<m[i][j]<<" ";
        }
        cout<<"\n";
    }
}