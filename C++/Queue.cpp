#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    int currentSize;
    const int maxSize = 5;
    T array[5];
    int head;
    int tail;

public:
    Queue() : currentSize(0), head(-1), tail(-1) {}
    //~Queue();

    bool isFull() {
        return currentSize == maxSize;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    void Enqueue(const T& val) {
        if (!isFull()) {
            tail = (tail + 1) % maxSize;
            array[tail] = val;
            if (!currentSize) {
                head = tail = 0;
            }
            ++currentSize;
        }
    }

    void Dequeue() {
        if (!isEmpty()) {
            head = (head + 1) % maxSize;
        }
        currentSize--;
    }

    void display() {
        int temp = head;
        cout << "head: " << head << endl;
        cout << "tail: " << tail << endl;
        while (temp != tail) {
            cout << array[temp] << " ";
            ++temp;
            temp = temp % maxSize;
        }
        cout << array[tail] << endl;
    }
};


int main() {
    int choice;
    Queue<int> q;

    do {
        cout << "\n=== Queue Menu ===\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "Enter value to enqueue: ";
                cin >> val;
                q.Enqueue(val);
                break;
            }
            case 2:
                q.Dequeue();
                break;
            case 3:
                q.display();
                cout << "[Display function not implemented yet]\n";
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}

