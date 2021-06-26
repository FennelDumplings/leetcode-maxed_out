//interview04.10: 检查子树

/*
 * https://leetcode-cn.com/problems/check-subtree-lcci/
 */

#include "../../include/Node.h"

class Solution {
public:
    bool checkSubTree(TreeNode* t1, TreeNode* t2) {
        if(!t2) return true;
        if(!t1) return false;
        return _preOrder(t1, t2);
    }

private:
    bool _preOrder(TreeNode* node, const TreeNode* t)
    {
        if(node -> val == t -> val)
        {
            if(!node -> left && !t -> left && !node -> right && !t -> right)
                return true;
            if(node -> left && t -> left && !node -> right && !t -> right)
                if(_preOrder(node -> left, t -> left))
                    return true;
            if(!node -> left && !t -> left && node -> right && t -> right)
                if(_preOrder(node -> right, t -> right))
                    return true;
            if(node -> left && t -> left && node -> right && t -> right)
                if(_preOrder(node -> left, t -> left) && _preOrder(node -> right, t -> right))
                    return true;
        }
        if(node -> left && _preOrder(node -> left, t))
            return true;
        if(node -> right && _preOrder(node -> right, t))
            return true;
        return false;
    }
};
