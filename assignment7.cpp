#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V + 1);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void displayGraph() {
        cout << "Graph Adjacency List:\n";
        for (int i = 1; i <= V; i++) {
            cout << "Node " << i << " -> ";
            for (auto edge : adj[i]) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }

    int spanningTree() {
        vector<bool> vis(V + 1, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});
        int sum = 0;

        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;

            if (vis[node]) continue;

            vis[node] = true;
            sum += wt;

            for (auto it : adj[node]) {
                int neighbour = it.first;
                int edge = it.second;
                if (!vis[neighbour]) {
                    pq.push({edge, neighbour});
                }
            }
        }
        return sum;
    }
};

int main() {
    int V, E;
    cin >> V >> E;

    Graph g(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.displayGraph();
    cout << "Minimum Spanning Tree Weight: " << g.spanningTree() << endl;

    return 0;
}
