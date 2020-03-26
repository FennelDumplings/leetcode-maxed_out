// prob114: Flatten Binary Tree to Linked List

/*
 * Given a binary tree, flatten it to a linked list in-place.
 */

/*
 * For example, given the following tree:
 *     1
 *    / \
 *   2   5
 *  / \   \
 * 3   4   6
 * The flattened tree should look like:
 *
 * 1
 *  \
 *   2
 *    \
 *     3
 *      \
 *       4
 *        \
 *         5
 *          \
 *           6
 */

#include "include/Node.h"

class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;

        TreeNode tree_node(0);
        TreeNode *dummy = &tree_node;
        //TreeNode *dummy = new TreeNode(0);
        dummy -> left = root;
        TreeNode *iter = dummy;
        _preOrder(root, iter);
        iter = dummy;
        while(iter -> left)
        {
            iter -> right = iter -> left;
            iter -> left = nullptr;
            iter = iter -> right;
        }
        root = dummy -> right;
        //delete dummy;
    }

private:
    void _preOrder(TreeNode* root, TreeNode*& iter)
    {
        iter -> left = root;
        iter = iter -> left;

        if(root -> left)
            _preOrder(root -> left, iter);
        if(root -> right)
            _preOrder(root -> right, iter);
    }
};
