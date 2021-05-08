// prob1110: Delete Nodes And Return Forest

/*
 * https://leetcode-cn.com/problems/delete-nodes-and-return-forest/
 */

#include <vector>
#include "include/Node.h"
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        if(!root) return {};
        setting = unordered_set<int>(to_delete.begin(), to_delete.end());
        vector<TreeNode*> result;
        TreeNode *res = _postOrder(root, result);
        if(res)
            result.push_back(res);
        return result;
    }

private:
    unordered_set<int> setting;

    TreeNode* _postOrder(TreeNode* node, vector<TreeNode*>& result)
    {
        TreeNode *left = nullptr, *right = nullptr;
        if(node -> left)
            left = _postOrder(node -> left, result);
        if(node -> right)
            right = _postOrder(node -> right, result);
        if(setting.count(node -> val) > 0)
        {
            if(left)
                result.push_back(left);
            if(right)
                result.push_back(right);
            return nullptr;
        }
        else
        {
            node -> left = left;
            node -> right = right;
            return node;
        }
    }
};
