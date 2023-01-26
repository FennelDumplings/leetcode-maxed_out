// interview26: 树的子结构

/*
 * https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/
 */

#include "../../include/Node.h"

class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(!A || !B) return false;
        return _preOrder(A, B);
    }

private:
    bool _preOrder(TreeNode* nodeA, TreeNode* B)
    {
        if(check(nodeA, B))
            return true;
        if(nodeA -> left)
            if(_preOrder(nodeA -> left, B))
                return true;
        if(nodeA -> right)
            if(_preOrder(nodeA -> right, B))
                return true;
        return false;
    }

    bool check(TreeNode* nodeA, TreeNode* nodeB)
    {
        if(nodeA -> val != nodeB -> val)
            return false;
        if(nodeB -> left && !nodeA -> left)
            return false;
        if(nodeB -> right && !nodeA -> right)
            return false;
        if(nodeB -> left)
            if(!check(nodeA -> left, nodeB -> left))
                return false;
        if(nodeB -> right)
            if(!check(nodeA -> right, nodeB -> right))
                return false;
        return true;
    }
};
