#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -----------------------------------------
// MIN HEAP FUNCTIONS
// -----------------------------------------

void heapUp(vector<int>& heap, int value, int freq[]) {
    heap.push_back(value);
    int i = heap.size() - 1;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (freq[heap[parent]] <= freq[heap[i]]) break;
        swap(heap[parent], heap[i]);
        i = parent;
    }
}

int heapDown(vector<int>& heap, int freq[]) {
    int top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    int i = 0;
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap.size() && freq[heap[left]] < freq[heap[smallest]])
            smallest = left;

        if (right < heap.size() && freq[heap[right]] < freq[heap[smallest]])
            smallest = right;

        if (smallest == i) break;

        swap(heap[i], heap[smallest]);
        i = smallest;
    }
    return top;
}

// -----------------------------------------
// DFS TO GENERATE CODES
// -----------------------------------------
void generateCodes(int node, string currentCode, int leftChild[], int rightChild[], string codes[], bool isLeaf[]) 
{
    if (isLeaf[node]) {
        codes[node] = currentCode;
        return;
    }

    generateCodes(leftChild[node],  currentCode + "0",
                  leftChild, rightChild, codes, isLeaf);

    generateCodes(rightChild[node], currentCode + "1",
                  leftChild, rightChild, codes, isLeaf);
}

// -----------------------------------------
// MAIN
// -----------------------------------------
int main() {
    string text = "hello huffman";

    // -------------------------------------
    // Step 1: Count frequencies (array only)
    // -------------------------------------
    char chars[256];
    int freq[256];
    bool used[256];

    for (int i = 0; i < 256; i++) {
        used[i] = false;
        freq[i] = 0;
    }

    for (char c : text)
        freq[(unsigned char)c]++;

    // Collect only used characters
    vector<char> letters;
    vector<int> frequencies;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            letters.push_back((char)i);
            frequencies.push_back(freq[i]);
        }
    }

    int n = letters.size();

    // -------------------------------------
    // Step 2: Build Huffman Tree Using Arrays
    // -------------------------------------
    int leftChild[512], rightChild[512];
    int nodeFreq[512];
    bool isLeaf[512];

    // Copy leaf nodes into the tree arrays
    for (int i = 0; i < n; i++) {
        leftChild[i] = rightChild[i] = -1;
        nodeFreq[i] = frequencies[i];
        isLeaf[i] = true;
    }

    vector<int> heap;

    // Push all leaf nodes into min-heap
    for (int i = 0; i < n; i++)
        heapUp(heap, i, nodeFreq);

    int nextNode = n; // next index for internal nodes

    while (heap.size() > 1) {
        int a = heapDown(heap, nodeFreq);
        int b = heapDown(heap, nodeFreq);

        leftChild[nextNode] = a;
        rightChild[nextNode] = b;
        nodeFreq[nextNode] = nodeFreq[a] + nodeFreq[b];
        isLeaf[nextNode] = false;

        heapUp(heap, nextNode, nodeFreq);
        nextNode++;
    }

    int root = heap[0];

    // -------------------------------------
    // Step 3: Generate Codes
    // -------------------------------------
    string codes[512];
    generateCodes(root, "", leftChild, rightChild, codes, isLeaf);

    // Print codes
    cout << "Huffman Codes:\n";
    for (int i = 0; i < n; i++) {
        cout << letters[i] << " : " << codes[i] << endl;
    }

    // -------------------------------------
    // Step 4: Encode
    // -------------------------------------
    string encoded = "";
    for (char c : text) {
        for (int i = 0; i < n; i++) {
            if (letters[i] == c) {
                encoded += codes[i];
                break;
            }
        }
    }

    cout << "\nEncoded string:\n" << encoded << endl;

    return 0;
}
