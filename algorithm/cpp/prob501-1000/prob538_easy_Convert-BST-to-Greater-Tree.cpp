// prob538: Convert BST to Greater Tree

/*
 * Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is
 * changed to the original key plus sum of all keys greater than the original key in BST.
 */

/*
 * Example:
 * Input: The root of a Binary Search Tree like this:
 *               5
 *             /   \
 *            2     13
 * Output: The root of a Greater Tree like this:
 *              18
 *             /   \
 *           20     13
 */

#include "include/Node.h"

class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        if(!root) return nullptr;
        TreeNode *precursor = nullptr;
        _inOrderReverse(root, precursor);
        return root;
    }

private:
    void _inOrderReverse(TreeNode* root, TreeNode*& precursor)
    {
        if(root -> right)
            _inOrderReverse(root -> right, precursor);

        if(precursor)
            root -> val += precursor -> val;
        precursor = root;

        if(root -> left)
            _inOrderReverse(root -> left, precursor);
    }
};
