#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Edge{
    int u, v, w;
};

int main(){
    srand(time(0));

    int n=10;
    int e=51;
    int s=0;

    vector<Edge> list(e);


    cout<<"n= "<<n<<" e= "<<e<<" s:"<<s<<endl;
    cout<<"Edges (u, v, weight):"<<endl;

    for(int i=0;i<e;++i){
        list[i].u=rand()%n;
        list[i].v=rand()%n;
        list[i].w=rand()%20+1;
        cout<<list[i].u<<" "<<list[i].v<<" "<<list[i].w<<endl;
    }

    vector<int> dist(n,1e9);
    dist[s]=0;

    for(int rep=0;rep<n-1;++rep){
        for(int i=0;i<e;++i){
            if(dist[list[i].u]<1e9 && dist[list[i].u]+list[i].w<dist[list[i].v]){
                dist[list[i].v]=dist[list[i].u]+list[i].w;
            }
        }
    }

    for(int i=0;i<n;++i){
        if(dist[i]==1e9){
            cout<<i<<": "<<"INF"<<endl;
        }
        else{
            cout<<i<<": "<<dist[i]<<" ";
        }
    }
    cout<<endl;

    return 0;
}
