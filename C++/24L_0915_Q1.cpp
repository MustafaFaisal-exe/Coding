#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    
    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;
    
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    Node* insert(Node* node, int val) {
        if (!node) {
            return new Node(val);
        }
        
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        } else {
            return node; // Duplicate values not allowed
        }
        
        updateHeight(node);
        
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && val < node->left->data) {
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && val > node->right->data) {
            return rotateLeft(node);
        }
        
        // Left Right Case
        if (balance > 1 && val > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left Case
        if (balance < -1 && val < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }
    
    // YOU WILL IMPLEMENT THIS RECURSIVE FUNCTION
    int findValue(Node* node, int value) {
        if (node) {
            if (node->data > value) {
                return findValue(node->left, value);
                
            } else {
                return findValue(node->right, value);
            }
        }
        return -1;
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int val) {
        root = insert(root, val);
    }
    
    void inorder() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }
    
    // Public wrapper for findValue
    int findValue(int value) {
        return findValue(root, value);
    }
};

int main() {
    AVLTree tree;
    
    // Building the AVL tree from the example
    tree.insert(25);
    tree.insert(8);
    tree.insert(43);
    tree.insert(3);
    tree.insert(15);
    tree.insert(27);
    tree.insert(65);
    tree.insert(19);
    
    cout << "AVL Tree created:" << endl;
    tree.inorder();
    cout << endl;
    
    // Test cases from the problem
    cout << "Test Case 1: Input = 8" << endl;
    cout << "Result: " << tree.findValue(8) << endl;
    cout << "Expected: 8" << endl << endl;
    
    cout << "Test Case 2: Input = 26" << endl;
    cout << "Result: " << tree.findValue(26) << endl;
    cout << "Expected: 27" << endl << endl;
    
    cout << "Test Case 3: Input = 22" << endl;
    cout << "Result: " << tree.findValue(22) << endl;
    cout << "Expected: 25" << endl << endl;
    
    cout << "Test Case 4: Input = 67" << endl;
    cout << "Result: " << tree.findValue(67) << endl;
    cout << "Expected: -1" << endl << endl;
    
    // Additional test cases
    cout << "Test Case 5: Input = 3" << endl;
    cout << "Result: " << tree.findValue(3) << endl;
    cout << "Expected: 3" << endl << endl;
    
    cout << "Test Case 6: Input = 50" << endl;
    cout << "Result: " << tree.findValue(50) << endl;
    cout << "Expected: 65" << endl << endl;
    
    return 0;
}