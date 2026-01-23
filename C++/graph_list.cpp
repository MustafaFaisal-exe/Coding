#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class GraphList {
private:
    int V;                         // number of vertices
    vector<vector<int>> adj;       // adjacency list

public:
    // Constructor
    GraphList(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Add edge (undirected by default)
    void addEdge(int u, int v, bool directed = false) {
        adj[u].push_back(v);
        if (!directed)
            adj[v].push_back(u);
    }

    // Print adjacency list
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < adj[v].size(); i++) {
            DFSUtil(adj[v][i], visited);
        }
    }

    // DFS (you will write this)
    void DFS(int start) {
        vector<bool> visited(V, false);

        DFSUtil(start, visited);
    }

    // BFS (you will write this)
    void BFS(int start) {
        // TODO: implement BFS
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            for (int i = 0; i < adj[current].size(); i++) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(adj[current][i]);
                }
            }
        }
    }
};
