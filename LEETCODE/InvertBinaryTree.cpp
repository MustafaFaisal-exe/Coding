/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void swapInorder(TreeNode*& root) {
        if (root) {
            if (root->left && root->right) {
                TreeNode* tmp = root->left;
                root->left = root->right;
                root->right = tmp;
            } else if (root->left && !root->right) {
                root->right = root->left;
                root->left = nullptr;
            } else if (!root->left && root->right) {
                root->left = root->right;
                root->right = nullptr;
            }

            swapInorder(root->left);
            swapInorder(root->right);
        }
    }

    TreeNode* invertTree(TreeNode* root) {
        swapInorder(root);
        return root;
    }
};