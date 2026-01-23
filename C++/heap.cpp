#include <iostream>
#include <vector>
using namespace std;

template <class T>
class BinaryHeap{
    private:
        vector<T> data;
        int size;
        int capacity;

        void swap(T& first, T& last) {
            T tmp = first;
            first = last;
            last = tmp;
        }

        void reheapUp(int last) {
            while (last > 0) {
                int parent = (last - 1) / 2;
                if (data[parent] < data[last]) {
                    swap(data[parent], data[last]);
                    last = parent;
                } else {
                    break;
                }
            }
        }

        void reheapDown(int root) {
            int left, right, max;

            while (true) {
                left = 2 * root + 1;
                right = 2 * root + 2;
                if (left >= size)
                    break;
                
                if (right < size && data[right] > data[left]) {
                    max = right;
                } else {
                    max = left;
                }

                if (data[root] < data[max]) {
                    swap(data[root], data[max]);
                    root = max;
                } else {
                    break;
                }
            }
        }

    public:
        BinaryHeap() : capacity(100), size(0) {
            data.resize(capacity);
        }

        bool isEmpty() const {
            return size == 0;
        }

        void insert(const T& val) {
            if (size == capacity) {
                capacity *= 2;
                data.resize(capacity);
            }

            data[size] = val;
            reheapUp(size);
            ++size;
        }

        T deleteMax() {
            if (isEmpty()) {
                throw runtime_error("Heap Empty");
            }

            T max = data[0];
            data[0] = data[size - 1];
            --size;
            reheapDown(0);
            return max;
        }

        void print() {
            for (int i = 0; i < size; i++) 
                cout << data[i] << " ";

            cout << endl;
        }

        void buildHeap(const vector<T>& arr) {
            data = arr;
            size = arr.size();

            if (size > capacity) {
                capacity = size;
                data.resize(capacity);
            }

            for (int i = size / 2 - 1; i >= 0; --i) {
                reheapDown(i);
            }
        }

        vector<T> heapSort() {
            vector<T> temp = data;
            int tmpSize = size;

            vector<T> sort(size);

            for (int i = size - 1; i >= 0; --i) {
                sort[i] = deleteMax();
            }

            data = temp;
            size = tmpSize;
            return sort;
        }
};

int main() {
    BinaryHeap<int> h;

    cout << "===== INSERT TEST =====\n";
    h.insert(30);
    h.insert(10);
    h.insert(50);
    h.insert(40);

    cout << "Heap after insertions: ";
    h.print();              // expected: 50 40 30 10
    
    
    cout << "\n===== DELETEMAX TEST =====\n";
    cout << "Deleted max: " << h.deleteMax() << endl;

    cout << "Heap after deleteMax: ";
    h.print();              // expected: 40 10 30
    

    cout << "\n===== BUILDHEAP TEST =====\n";
    vector<int> arr = {20, 5, 70, 40, 10, 60, 30};

    cout << "Array before buildHeap: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    h.buildHeap(arr);

    cout << "Heap after buildHeap:  ";
    h.print();              // expected max heap


    cout << "\n===== HEAPSORT TEST =====\n";

    vector<int> sorted = h.heapSort();

    cout << "Sorted array from heapSort: ";
    for (int x : sorted) cout << x << " ";
    cout << endl;


    cout << "\n===== FINAL HEAP (UNCHANGED AFTER HEAPSORT) =====\n";
    h.print();              // should show original heap restored

    return 0;
}
