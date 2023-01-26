// prob700: Search in a Binary Search Tree

/*
 * Given the root node of a binary search tree (BST) and a value. You need to find the node in the BST that the node's value
 * equals the given value. Return the subtree rooted with that node. If such node doesn't exist, you should return NULL.
 */

#include "include/Node.h"

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(!root) return nullptr;
        return _preOrder(root, val);
    }

private:
    TreeNode* _preOrder(TreeNode* root, int val)
    {
        if(root -> val == val)
            return root;
        if(root -> val > val && root -> left)
            return _preOrder(root -> left, val);
        if(root -> val < val && root -> right)
            return _preOrder(root -> right, val);
        return nullptr;
    }
};
