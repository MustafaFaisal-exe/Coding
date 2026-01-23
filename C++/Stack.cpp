#include <iostream>
#include <vector>
using namespace std;

class minHeap {
private:
    vector<int> heap;
    
    int parent(int i) {
        return (i - 1) / 2;
    }
    
    int leftChild(int i) {
        return 2 * i + 1;
    }
    
    int rightChild(int i) {
        return 2 * i + 2;
    }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }
        
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }
        
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    
public:
    minHeap() {}
    
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMin() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return minVal;
    }
    
    void display() {
        cout << "Heap: ";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
    
    int size() {
        return heap.size();
    }
    
    void updateKey(int k, int v) {
        // You will implement this function
        if (heap[k] > v) {
            //heapify down
            heap[k] = v;

            while (k < heap.size()) {
                int left, right, min;
                left = 2 * k + 1;
                right = 2 * k + 2;

                if (left >= heap.size()) {
                    break;
                }

                if (right < heap.size() && heap[right] < heap[left]) {
                    min = right;
                } else {
                    min = left;
                }

                if (heap[k] > heap[min]) {
                    swap(heap[k], heap[min]);
                    k = min;
                } else {
                    break;
                }
            }
        } else {
            //heapify up
            heap[k] = v;

            while (k > 0) {
                int parent = (k - 1) / 2;

                if (heap[parent] > heap[k]) {
                    swap(heap[parent], heap[k]);
                    k = parent;
                } else {
                    break;
                }
            }
        }
    }
};

int main() {
    minHeap h;
    
    // Building a sample min heap
    h.insert(5);
    h.insert(3);
    h.insert(7);
    h.insert(1);
    h.insert(9);
    h.insert(8);
    h.insert(6);
    
    cout << "Original heap:" << endl;
    h.display();
    
    // Test updateKey - decreasing a key
    cout << "\nUpdating key at index 4 to value 0:" << endl;
    h.updateKey(4, 0);
    h.display();
    
    // Test updateKey - increasing a key
    cout << "\nUpdating key at index 1 to value 10:" << endl;
    h.updateKey(1, 10);
    h.display();
    
    // Test updateKey - same value
    cout << "\nUpdating key at index 2 to value 7:" << endl;
    h.updateKey(2, 7);
    h.display();
    
    return 0;
}