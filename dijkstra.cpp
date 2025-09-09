#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;


void dijkstra(int src, const vector<vector<pair<int, int>>>& adjList, int nodes) {

    vector<int> dist(nodes, INT_MAX);
    dist[src] = 0;


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int currNode = pq.top().second;
        pq.pop();


        if (currDist > dist[currNode]) {
            continue;
        }


        for (int i = 0; i < adjList[currNode].size(); ++i) {
            int neighbor = adjList[currNode][i].first;
            int weight = adjList[currNode][i].second;


            if (dist[currNode] + weight < dist[neighbor]) {
                dist[neighbor] = dist[currNode] + weight;
                pq.push(make_pair(dist[neighbor], neighbor));
            }
        }
    }

    cout << src << ":" << endl;
    for (int i = 0; i < nodes; ++i) {
        cout << "Node " << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
    }
}

int main() {
    int nodes = 6;
    vector<vector<pair<int, int>>> adjList(nodes);
    adjList[0].push_back(make_pair(1, 4));
    adjList[0].push_back(make_pair(2, 1));
    adjList[1].push_back(make_pair(3, 1));
    adjList[2].push_back(make_pair(1, 2));
    adjList[2].push_back(make_pair(3, 5));
    adjList[3].push_back(make_pair(4, 3));
    dijkstra(0, adjList, nodes);

    return 0;
}