// interview17.12: BiNode

/*
 * https://leetcode-cn.com/problems/binode-lcci/
 */

#include "../../include/Node.h"

class Solution {
public:
    TreeNode* convertBiNode(TreeNode* root) {
        if(!root) return nullptr;
        TreeNode *result = nullptr, *prev = nullptr;
        _inOrder(root, prev, result);
        return result;
    }

private:
    void _inOrder(TreeNode* root, TreeNode*& prev, TreeNode*& result)
    {
        if(root -> left)
            _inOrder(root -> left, prev, result);
        if(!result)
        {
            result = root;
            prev = result;
        }
        else
        {
            prev -> right = root;
            root -> left = nullptr;
            prev = root;
        }
        if(root -> right)
            _inOrder(root -> right, prev, result);
    }
};
