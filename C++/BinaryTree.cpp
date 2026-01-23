#include <iostream>
using namespace std;

// ==========================
// Node structure for BST
// ==========================
template <class T>
class BNode {
public:
    T data;
    BNode* left;
    BNode* right;

    BNode(T d) : data(d), left(nullptr), right(nullptr) {}
};

// ==========================
// Binary Search Tree class
// ==========================
template <class T>
class BSTree {
private:
    BNode<T>* root;

    // Helper recursive insertion
    void insertRec(T val, BNode<T>*& node) {
        if (!node)
            node = new BNode<T>(val);
        else if (val < node->data)
            insertRec(val, node->left);
        else if (val > node->data)
            insertRec(val, node->right);
    }

    // Helper recursive search
    bool searchRec(T val, BNode<T>* node) {
        if (!node) return false;
        if (node->data == val) return true;
        else if (val < node->data) return searchRec(val, node->left);
        else return searchRec(val, node->right);
    }

    // Helper to find minimum value node
    BNode<T>* findMin(BNode<T>* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // Helper recursive delete
    void deleteRec(BNode<T>*& node, T val) {
        if (!node) return;
        if (val < node->data)
            deleteRec(node->left, val);
        else if (val > node->data)
            deleteRec(node->right, val);
        else {
            // Node found
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
            else if (!node->left) {
                BNode<T>* temp = node;
                node = node->right;
                delete temp;
            }
            else if (!node->right) {
                BNode<T>* temp = node;
                node = node->left;
                delete temp;
            }
            else {
                BNode<T>* minRight = findMin(node->right);
                node->data = minRight->data;
                deleteRec(node->right, minRight->data);
            }
        }
    }

    // Recursive traversals
    void inorder(BNode<T>* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(BNode<T>* node) {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(BNode<T>* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    void destroy(BNode<T>*& node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            node = nullptr;
        }
    }

public:
    BSTree() : root(nullptr) {}
    ~BSTree() { destroy(root); }

    void insert(T val) { insertRec(val, root); }
    bool search(T val) { return searchRec(val, root); }
    void remove(T val) { deleteRec(root, val); }

    void inorder() { inorder(root); cout << endl; }
    void preorder() { preorder(root); cout << endl; }
    void postorder() { postorder(root); cout << endl; }
};

// ==========================
// Example usage
// ==========================
int main() {
    BSTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder (sorted): "; tree.inorder();
    cout << "Preorder: "; tree.preorder();
    cout << "Postorder: "; tree.postorder();

    cout << "Searching 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    tree.remove(30);
    cout << "After deleting 30 (inorder): "; tree.inorder();
}
