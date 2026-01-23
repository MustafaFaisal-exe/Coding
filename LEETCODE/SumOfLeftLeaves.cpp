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
    void sum(TreeNode* root, int& summ) {
        if (root) {
            if (root->left && !root->left->left && !root->left->right) {
                summ += root->left->val;
            }

            sum(root->left, summ);
            sum(root->right, summ);
        }
    }

    int sumOfLeftLeaves(TreeNode* root) {
        int summ = 0;

        sum(root, summ);
        return summ;
    }
};