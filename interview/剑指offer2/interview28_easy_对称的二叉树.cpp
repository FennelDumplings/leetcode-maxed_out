// interview28: 对称的二叉树

/*
 * https://leetcode-cn.com/problems/dui-cheng-de-er-cha-shu-lcof/
 */

#include "../../include/Node.h"

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        if((!root -> left && !root -> right))
            return true;
        if((root -> left && !root -> right) || (!root -> left && root -> right))
            return false;
        if(root -> left -> val != root -> right -> val)
            return false;
        return _preOrder(root -> left, root -> right);
    }

private:
    bool _preOrder(TreeNode* node1, TreeNode* node2)
    {
        // 调用方保证 node1 和 node2 存在且值相同
        if(is_leaf(node1) && is_leaf(node2))
            return true;
        if(node1 -> left && !node2 -> right)
            return false;
        if(node1 -> right && !node2 -> left)
            return false;
        if(!node1 -> left && node2 -> right)
            return false;
        if(!node1 -> right && node2 -> left)
            return false;
        if(node1 -> left)
        {
            if(node1 -> left -> val != node2 -> right -> val)
                return false;
            if(!_preOrder(node1 -> left, node2 -> right))
                return false;
        }
        if(node1 -> right)
        {
            if(node1 -> right -> val != node2 -> left -> val)
                return false;
            if(!_preOrder(node1 -> right, node2 -> left))
                return false;
        }
        return true;
    }

    bool is_leaf(TreeNode* t)
    {
        return (!t -> left && !t -> right);
    }
};
