#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

class Graph {
public:
    int n;
    unordered_map<string, vector<string>> adj;
    unordered_map<string, bool> visited;

    Graph(int size) {
        n = size;
    }

    void insertEdge(string u, string v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfsHelper(string node) {
        if (visited[node]) return;

        visited[node] = true;
        cout << node << " ";

        for (auto& neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor);
            }
        }
    }

    void dfs(string start) {
        visited.clear();
        dfsHelper(start);
        cout << endl;
    }

    void bfs(string start) {
        visited.clear();
        queue<string> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            string node = q.front();
            q.pop();
            cout << node << " ";

            for (auto& neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g(8);

    g.insertEdge("College", "Library");
    g.insertEdge("College", "Cafeteria");
    g.insertEdge("Library", "Bookstore");
    g.insertEdge("Library", "Cafe");
    g.insertEdge("Cafeteria", "Gym");
    g.insertEdge("Gym", "Parking");
    g.insertEdge("Parking", "Library");

    cout << "DFS starting from College: ";
    g.dfs("College");

    cout << "BFS starting from College: ";
    g.bfs("College");

    return 0;
}
