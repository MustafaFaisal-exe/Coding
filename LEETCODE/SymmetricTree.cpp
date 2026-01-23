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
    bool isSame(TreeNode* p, TreeNode* q) {
        bool result;
        if (!p && !q) {
            result = true;
        } else if ((!p && q) || (p && !q)) {
            return false;
        } else if (p && q) {
            result = isSame(p->left, q->right);
            if (!result) {
                return result;
            }
            if (p->val == q->val) {
                result = true;
            } else {
                return false;
            }
            result = isSame(p->right, q->left);
            if (!result) {
                return result;
            }
        }
        return result;
    }


    bool isSymmetric(TreeNode* root) {
        return isSame(root->left, root->right);
    }
};