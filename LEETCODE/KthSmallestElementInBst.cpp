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
    void traverse(TreeNode* node, int& k, int& min) {
        if (node) {
            traverse(node->left, k, min);

            if (k != 0) {
                min = node->val;
                k--;
            }

            traverse(node->right, k, min);
        }
    }

    int kthSmallest(TreeNode* root, int k) {
        int kthsmall = INT_MAX;
        traverse(root, k, kthsmall);
        return kthsmall;
    }
};