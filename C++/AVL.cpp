#include <iostream>
using namespace std;

class AVL {
    private:
        class AVLnode {
            public:

            int data;
            AVLnode* left;
            AVLnode* right;
            int height;

            AVLnode(const int& val) : data(val), left(nullptr), right(nullptr), height(0) {}
        };

        AVLnode* root;

        int getHeight(AVLnode* node) {
            if (node) {
                return node->height;
            } else {
                return -1;
            }
        }

        void updateHeight(AVLnode* node) {
            if (node) {
                node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
            }
        }

        int getBalance(AVLnode* node) {
            if (node) {
                return getHeight(node->right) - getHeight(node->left);
            } else {
                return -1;
            }
        }

        void rotateLeft(AVLnode*& x) {
            AVLnode* y = x->right;
            AVLnode* orphan = nullptr;

            if (y) {
                orphan = y->left;
            }

            y->left = x;
            x->right = orphan;

            updateHeight(x);
            updateHeight(y);

            x = y;
        }

        void rotateRight(AVLnode*& x) {
            AVLnode* y = x->left;
            AVLnode* orphan = nullptr;

            if (y) {
                orphan = y->right;
            }

            y->right = x;
            x->left = orphan;

            updateHeight(x);
            updateHeight(y);

            x = y;
        }

        void balance(AVLnode*& node) {
            if (!node) {
                return;
            }

            updateHeight(node);

            int bf = getBalance(node);

            if (bf < -1) {
                if (getBalance(node->left) <= 0) {
                    rotateRight(node);
                } else {
                    rotateLeft(node);
                    rotateRight(node);
                }
            } else if (bf > 1) {
                if (getBalance(node->right) >= 0) {
                    rotateLeft(node);
                } else {
                    rotateRight(node);
                    rotateLeft(node);
                }
            }

            updateHeight(node);
        }

        void insert(AVLnode*& node, const int& val) {
            if (!node) {
                node = new AVLnode(val);
            }

            if (val < node->data) {
                insert(node->left, val);
            } else if (val > node->data) {
                insert(node->right, val);
            }

            balance(node);
        }

        AVLnode* findMin(AVLnode* node) {
            AVLnode* tmp = node;
            while (tmp && tmp->left) {
                tmp = tmp->left;
            }

            return tmp;
        }

        void deleteNode(AVLnode*& node, const int& val) {
            if (!node) {
                return;
            }

            if (val < node->data) {
                deleteNode(node->left, val);
            } else if (val > node->data) {
                deleteNode(node->right, val);
            } else {
                if (!node->left && !node->right) {
                    delete node;
                    node = nullptr;
                } else if (!node->left) {
                    AVLnode* tmp = node;
                    node = node->right;
                    delete tmp;
                } else if (!node->right) {
                    AVLnode* tmp = node;
                    node = node->left;
                    delete tmp;
                } else {
                    AVLnode* min = findMin(node->right);
                    node->data = min->data;
                    deleteNode(node->right, min->data);
                }
            }

            balance(node);
        }


        void inorder(AVLnode* node) {
            if (node) {
                inorder(node->left);
                cout << node->data << " ";
                inorder(node->right);
            }
        }

    public:
        AVL() : root(nullptr) {}

        void insert(int val) {
            insert(root, val);
        }

        void remove(int val) {
            deleteNode(root, val);
        }

        void display() {
            inorder(root);
        }

};

int main() {
    AVL tree;

    cout << "Inserting elements...\n";
    int values[] = {10, 20, 30, 40, 50, 25};
    for (int val : values) {
        cout << "Insert " << val << ": ";
        tree.insert(val);
        tree.display();
        cout << endl;
    }

    cout << "\nFinal AVL tree (inorder): ";
    tree.display();
    cout << endl;

    cout << "\nDeleting 40...\n";
    tree.remove(40);
    tree.display();
    cout << endl;

    cout << "Deleting 30...\n";
    tree.remove(30);
    tree.display();
    cout << endl;

    cout << "Deleting 10...\n";
    tree.remove(10);
    tree.display();
    cout << endl;

    return 0;
}
