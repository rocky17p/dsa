#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class edge
{
public:
    int u;
    int v;
    int w;
    edge(int u, int v, int w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
};
bool compare(edge a, edge b)
{
    return a.w < b.w;
}
class graph
{
public:
    int v;
    vector<vector<pair<int, int>>> adj;
    vector<edge> edges;
    graph(int v)
    {
        this->v = v;
        adj.resize(v + 1);
    }
    void addedge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back(edge(u, v, w));
    }
    void prims()
    {
        int mst = 0;
        vector<bool> visited(v + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});
        while (!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            int wt = it.first;
            int node = it.second;
            if (visited[node])
                continue;
            visited[node] = true;
            mst += wt;
            for (auto it : adj[node])
            {
                int edgew = it.second;
                int neigh = it.first;
                if (!visited[neigh])
                {
                    pq.push({edgew, neigh});
                }
            }
        }
        cout << "mst cost is  " << mst << endl;
    }
    int findparent(int node, vector<int> &parent)
    {
        while (node != parent[node])
        {
            node = parent[node];
        }
        return parent[node];
    }
    void kruskals()
    {
        int mst = 0;
        vector<int> parent(v + 1);
        for (int i = 0; i <= v; i++)
        {
            parent[i] = i;
        }
        sort(edges.begin(), edges.end(), compare);
        cout << "edges in mst" << endl;
        for (auto s : edges)
        {
            int u = s.u;
            int v = s.v;
            int w = s.w;
            int pu = findparent(s.u, parent);
            int pv = findparent(s.v, parent);
            if (pu != pv)
            {
                cout << u << "-" << v << ":" << w << endl;
                mst += w;
                parent[pu] = pv;
            }
        }
        cout << "mst cost is  " << mst << endl;
    }
    void display()
    {
        for (int i = 1; i <= v; i++)
        {
            cout << "Node" << i << "->";
            for (auto it : adj[i])
            {
                cout << "(" << it.first << "," << it.second << ")";
            }
            cout << endl;
        }
    }
};
int main()
{
    int v, e;
    cout << "enter the number of vertices" << endl;
    cin >> v;
    cout << "enter the number of edges" << endl;
    cin >> e;
    graph g(v);
    cout << "enter " << e << " edges in format :u,v,w" << endl;
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addedge(u, v, w);
    }
    int choice;
    do
    {
        cout << "Menu" << endl;
        cout << "1.add edge" << endl;
        cout << "2.display graph" << endl;
        cout << "3.prims" << endl;
        cout << "4.kruskals" << endl;
        cout << "5.exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "enter the edge in format u,v,w" << endl;
            int u, v, w;
            cin >> u >> v >> w;
            g.addedge(u, v, w);
            break;
        }
        case 2:
        {
            g.display();
            break;
        }
        case 3:
        {
            g.prims();
            break;
        }
        case 4:
        {
            g.kruskals();
            break;
        }
        case 5:
        {
            cout << "exiting...." << endl;
            return 0;
        }
        default:
        {
            cout << "enter valid choice" << endl;
            break;
        }
        }
    } while (choice != 5);
    return 0;
}
