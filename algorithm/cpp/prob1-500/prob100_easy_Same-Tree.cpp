// prob100: Same Tree

/*
 * Given two binary trees, write a function to check if they are the same or not.
 * Two binary trees are considered the same if they are structurally identical and the nodes have the same value.
 */

#include "include/Node.h"

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return _preOrder(p, q);
    }

private:
    bool _preOrder(TreeNode* p, TreeNode* q)
    {
        if(!p && !q)
            return true;
        if(!p || !q)
            return false;
        bool result = true;
        result = result && (p -> val == q -> val);
        if(!result) return false;
        result = result && _preOrder(p -> left, q -> left);
        if(!result) return false;
        result = result && _preOrder(p -> right, q -> right);
        return result;
    }
};
