#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Graph {
public:
    unordered_map<string, vector<pair<string, int>>> adj;
    unordered_map<string, bool> visited;
    unordered_set<string> cities;

    void addEdge(string u, string v, int cost) {
        adj[u].push_back({v, cost});
        // If undirected, also do: adj[v].push_back({u, cost});
        cities.insert(u);
        cities.insert(v);
    }

    void dfsHelper(string node) {
        if (visited[node]) return;

        visited[node] = true;
        cout << node << " ";

        for (auto& neighbor : adj[node]) {
            if (!visited[neighbor.first]) {
                dfsHelper(neighbor.first);
            }
        }
    }

    void dfs(string start) {
        visited.clear();
        cout << "\nDFS from " << start << ": ";
        dfsHelper(start);
        cout << endl;
    }

    void calculateDegrees() {
        unordered_map<string, int> indegree, outdegree;

        for (auto it : adj) {
            outdegree[it.first] = it.second.size();
        }

        for (auto it : adj) {
            for (auto to : it.second) {
                indegree[to.first]++;
            }
        }

        cout << "\nDegrees:\n";
        for (auto city : cities) {
            cout << city << " - In: " << indegree[city] << ", Out: " << outdegree[city] << endl;
        }
    }

    bool isConnected(string start) {
        visited.clear();
        dfsHelper(start);
        for (auto city : cities) {
            if (!visited[city]) return false;
        }
        return true;
    }
};

int main() {
    Graph g;
    int choice;
    string u, v, start;
    int cost;

    while (true) {
        cout << "\nMenu: \n";
        cout << "1. Add Edge\n";
        cout << "2. Perform DFS\n";
        cout << "3. Calculate Degrees (In and Out)\n";
        cout << "4. Check if Graph is Connected\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Add edge to graph
                cout << "Enter source city: ";
                cin >> u;
                cout << "Enter destination city: ";
                cin >> v;
                cout << "Enter cost (time/fuel): ";
                cin >> cost;
                g.addEdge(u, v, cost);
                break;
            
            case 2:
                // Perform DFS
                cout << "Enter start city for DFS: ";
                cin >> start;
                g.dfs(start);
                break;
            
            case 3:
                // Calculate Degrees
                g.calculateDegrees();
                break;
            
            case 4:
                // Check if Graph is Connected
                cout << "Enter start city to check connectivity: ";
                cin >> start;
                if (g.isConnected(start)) {
                    cout << "\nGraph is connected\n";
                } else {
                    cout << "\nGraph is NOT connected\n";
                }
                break;
            
            case 5:
                // Exit
                cout << "Exiting...\n";
                return 0;
            
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
