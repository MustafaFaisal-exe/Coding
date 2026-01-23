#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class GraphMatrix {
private:
    int V;                          // number of vertices
    vector<vector<int>> matrix;     // adjacency matrix

public:
    // Constructor
    GraphMatrix(int vertices) {
        V = vertices;
        matrix.resize(V, vector<int>(V, 0));
    }

    // Add edge (undirected by default)
    void addEdge(int u, int v, bool directed = false) {
        matrix[u][v] = 1;
        if (!directed)
            matrix[v][u] = 1;
    }

    // Print adjacency matrix
    void printGraph() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                visited[i] = true;
                DFSUtil(matrix[v][i], visited);
            }
        }
    }

    // DFS (you will write this)
    void DFS(int start) {
        // TODO: implement DFS
        vector<bool> visited(V, false);

        for (int it = 0; it < V; it++) {
            if (!visited[it])
                DFSUtil(it, visited);
        }
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

            for (int i = 0; i < matrix[current].size(); i++) {
                if (!visited[i] && matrix[current][i] == 1) {
                    visited[i] = true;
                    q.push(matrix[current][i]);
                }
            }
        }
    }
};
