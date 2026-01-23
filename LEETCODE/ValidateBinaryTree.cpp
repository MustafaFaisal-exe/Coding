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
    void inorder(TreeNode* node, vector<int>& arr) {
        if (node) {
            inorder(node->left, arr);

            arr.push_back(node->val);

            inorder(node->right, arr);
        }
    }
    bool isValidBST(TreeNode* root) {
        vector<int> array;
        inorder(root, array);

        for (int i = 0; i < array.size() - 1; i++) {
            if (array[i] >= array[i + 1]) {
                return false;
            }
        }
        return true;
    }
};