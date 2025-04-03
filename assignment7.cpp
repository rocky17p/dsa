#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int spanningTree(int V, vector<vector<int>> adj[]) {
    vector<bool>vis(V,false);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,0});
    int sum=0;
    while(!pq.empty()){
        auto it=pq.top();
        pq.pop();
        int node=it.second;
        int wt=it.first;
        if(vis[node]) continue;
        vis[node]=true;
        sum+=wt;
        for(auto it : adj[node]){
            int neighbour=it[0];
            int edge=it[1];
            if(!vis[neighbour]){
                pq.push({edge,neighbour});
            }
        }
    }
    return sum;
}
int main() {
    int V, E;
    cin >> V >> E;
    
    vector<vector<int>> adj[V];

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cout << "Minimum Spanning Tree Weight: " << spanningTree(V, adj) << endl;
    return 0;
}
