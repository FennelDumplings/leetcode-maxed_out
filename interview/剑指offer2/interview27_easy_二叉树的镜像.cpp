// interview27: 二叉树的镜像

/*
 * https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/
 */

#include "../../include/Node.h"

class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if(!root) return nullptr;
        _preOrder(root);
        return root;
    }

private:
    void _preOrder(TreeNode* node)
    {
        TreeNode *tmp = node -> left;
        node -> left = node -> right;
        node -> right = tmp;
        if(node -> left)
            _preOrder(node -> left);
        if(node -> right)
            _preOrder(node -> right);
    }
};
