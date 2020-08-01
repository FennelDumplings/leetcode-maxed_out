// interview04.06: 后继者

/*
 * https://leetcode-cn.com/problems/successor-lcci/
 */

#include "../../include/Node.h"

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode *result = nullptr;
        TreeNode *prev = nullptr;
        _inOrder(root, p, prev, result);
        return result;
    }

private:
    void _inOrder(TreeNode* node, const TreeNode* p, TreeNode*& prev, TreeNode*& result)
    {
        if(node -> left)
            _inOrder(node -> left, p, prev, result);

        if(result) return;
        if(prev)
        {
            if(prev == p)
            {
                result = node;
                return;
            }
        }
        prev = node;

        if(node -> right)
            _inOrder(node -> right, p, prev, result);
    }
};
