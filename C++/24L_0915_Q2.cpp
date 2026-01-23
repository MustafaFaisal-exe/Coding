#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

struct Hnode {
    double distance;
    int i, j;
};

class MinHeap {
    vector<Hnode> heap;

    void heapifyDown(int idx) {
        int n = heap.size();
        int smallest = idx;
        int left = 2*idx + 1;
        int right = 2*idx + 2;

        if (left < n && heap[left].distance < heap[smallest].distance)
            smallest = left;
        if (right < n && heap[right].distance < heap[smallest].distance)
            smallest = right;

        if (smallest != idx) {
            swap(heap[idx], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int idx) {
        while (idx > 0) {
            int parent = (idx-1)/2;
            if (heap[parent].distance <= heap[idx].distance) 
                break;

            swap(heap[parent], heap[idx]);
            idx = parent;
        }
    }

public:
    MinHeap() {}

    void insert(const Hnode& node) {
        heap.push_back(node);
        heapifyUp(heap.size()-1);
    }

    Hnode Min() {
        Hnode minNode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) 
            heapifyDown(0);

        return minNode;
    }

    bool empty() {
        return heap.empty();
    }
};

double roundTo(double value, int decimals) {
    double scale = pow(10, decimals);
    return round(value * scale)/scale;
}

double dist(double x1, double y1, double x2, double y2) {
    return roundTo(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)), 1);
}

int main() {
    ifstream file("points.txt");
    if (!file) { cout << "File not found\n"; return 1; }

    int n, m;
    file >> n >> m;

    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) 
        file >> x[i] >> y[i];

    file.close();

    vector<vector<double>> matrix(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(i+1);
        for (int j = 0; j <= i; j++)
            matrix[i][j] = dist(x[i], y[i], x[j], y[j]);
    }

    vector<list<int>> groups(n);
    for (int i = 0; i < n; i++) 
        groups[i].push_back(i);

    MinHeap heap;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            heap.insert({matrix[i][j], j, i});
        }
    }

    vector<bool> alive(n, true);

    while (n > m) {
        Hnode top;

        while (true) {
            top = heap.Min();
            if (alive[top.i] && alive[top.j]) 
                break;
        }

        int a = top.i;
        int b = top.j;
        cout << "\nMerging group " << a+1 << " and group " << b+1 << "\n";

        for (int i = 0; i < matrix.size(); i++) {
            if (!alive[i] || i == a) 
                continue;

            int small = min(i, a), 
            large = max(i, a);
            int smallb = min(i, b), 
            largeb = max(i, b);
            double d = min(matrix[large][small], matrix[largeb][smallb]);
            matrix[large][small] = d;

            heap.insert({d, small, large});
        }

        groups[a].splice(groups[a].end(), groups[b]);
        alive[b] = false;
        n--;
    }

    cout << "\nGroups after merging:\n";
    for (int i = 0; i < groups.size(); i++) {
        if (!alive[i]) 
            continue;
            
        cout << "Group " << i+1 << ": ";
        for (int idx : groups[i]) cout << "(" << x[idx] << "," << y[idx] << ") ";
            cout << endl;

    }

    return 0;
}
