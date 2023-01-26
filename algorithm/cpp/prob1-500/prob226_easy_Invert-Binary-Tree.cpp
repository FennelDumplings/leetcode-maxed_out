// prob226: Invert Binary Tree

/*
 * Invert a binary tree.
 */

/*
 * Example:
 * Input:
 *      4
 *    /   \
 *   2     7
 *  / \   / \
 * 1   3 6   9
 * Output:
 *      4
 *    /   \
 *   7     2
 *  / \   / \
 * 9   6 3   1
 */

#include "include/Node.h"
#include <algorithm>

using namespace std;

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return nullptr;
        _preOrder(root);
        return root;
    }

private:
    void _preOrder(TreeNode* root)
    {
        swap(root -> left, root -> right);
        if(root -> left)
            _preOrder(root -> left);
        if(root -> right)
            _preOrder(root -> right);
    }
};
