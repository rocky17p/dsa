#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V + 1);
    }

    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void displayGraph()
    {
        cout << "\nGraph Adjacency List:\n";
        for (int i = 1; i <= V; i++)
        {
            cout << "Node " << i << " -> ";
            for (auto edge : adj[i])
            {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }

    int prims()
    {
        vector<bool> visited(V + 1, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});
        int sum = 0;

        while (!pq.empty())
        {
            auto it = pq.top();
            int wt = it.first;
            int node = it.second;
            pq.pop();

            if (visited[node])
                continue;

            sum += wt;
            visited[node] = true;

            for (auto it : adj[node])
            {
                int neighbour = it.first;
                int edgewt = it.second;
                if (!visited[neighbour])
                {
                    pq.push({edgewt, neighbour});
                }
            }
        }

        return sum;
    }
};

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Enter " << E << " edges in format: u v w\n";
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. Find MST using Prim's Algorithm\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
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
            cout << "Minimum Spanning Tree Weight: " << g.prims() << endl;
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
