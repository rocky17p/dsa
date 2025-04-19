#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Edge {
public:
    int u, v, weight;
    Edge(int u, int v, int w) {
        this->u = u;
        this->v = v;
        this->weight = w;
    }
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;
    vector<Edge> edges;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V + 1); // 1-based indexing
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back(Edge(u, v, w));
    }

    void displayGraph() {
        cout << "\nGraph Adjacency List:\n";
        for (int i = 1; i <= V; i++) {
            cout << "Node " << i << " -> ";
            for (auto it : adj[i]) {
                cout << "(" << it.first << ", " << it.second << ") ";
            }
            cout << endl;
        }
    }

    int prims() {
        vector<bool> visited(V + 1, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1}); // start from node 1
        int sum = 0;

        while (!pq.empty()) {
            auto it = pq.top();
            int wt = it.first;
            int node = it.second;
            pq.pop();

            if (visited[node])
                continue;

            sum += wt;
            visited[node] = true;

            for (auto it : adj[node]) {
                int neighbour = it.first;
                int edgewt = it.second;
                if (!visited[neighbour]) {
                    pq.push({edgewt, neighbour});
                }
            }
        }

        return sum;
    }

    int kruskal() {
        sort(edges.begin(), edges.end(), compare);
        vector<int> parent(V + 1);
        for (int i = 1; i <= V; i++) {
            parent[i] = i;
        }

        int mstWeight = 0;
        cout << "\nEdges in Kruskal's MST:\n";
        for (auto edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.weight;

            int pu = findParent(u, parent);
            int pv = findParent(v, parent);

            if (pu != pv) {
                cout << u << " - " << v << " : " << w << endl;
                mstWeight += w;
                parent[pu] = pv;
            }
        }

        return mstWeight;
    }

    int findParent(int node, vector<int>& parent) {
        while (node != parent[node])
            node = parent[node];
        return node;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Enter " << E << " edges in format: u v w\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. Find MST using Prim's Algorithm\n";
        cout << "4. Find MST using Kruskal's Algorithm\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int u, v, w;
            cout << "Enter edge (u v w): ";
            cin >> u >> v >> w;
            g.addEdge(u, v, w);
            break;
        }
        case 2:
            g.displayGraph();
            break;
        case 3:
            cout << "Minimum Spanning Tree Weight (Prim's): " << g.prims() << endl;
            break;
        case 4:
            cout << "Minimum Spanning Tree Weight (Kruskal's): " << g.kruskal() << endl;
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
