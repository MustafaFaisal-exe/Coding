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
    int maxD(TreeNode* root, int maxCount) {
        int count = 0;
        if (root) {
            count = maxD(root->left, count++);
            count = maxD(root->right, count++);
            count++;
        }
        if (count > maxCount) {
            maxCount = count;
        }
        return maxCount;
    }
    int maxDepth(TreeNode* root) {
        return maxD(root, 0);

    }
};