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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        bool result;
        if (!p && !q) {
            result = true;
        } else if ((!p && q) || (p && !q)) {
            return false;
        } else if (p && q) {
            result = isSameTree(p->left, q->left);
            if (!result) {
                return result;
            }
            if (p->val == q->val) {
                result = true;
            } else {
                return false;
            }
            result = isSameTree(p->right, q->right);
            if (!result) {
                return result;
            }
        }
        return result;
    }
};