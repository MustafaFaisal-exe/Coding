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
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> level;
        vector<vector<int>> res;
        int i = 0;

        if (root) {
            level.push(root);
    
            while (!level.empty()) {
    
                vector<int> tmp;
                int size = level.size();
                for (int i = 0; i < size; i++) {
                    TreeNode* current = level.front();
                    tmp.push_back(current->val);
                    level.pop();

                    if (current->left) {
                        level.push(current->left);
                    }

                    if (current->right) {
                        level.push(current->right);
                    }
                }
                res.push_back(tmp);
            }
        }
        
        return res;
    }
};