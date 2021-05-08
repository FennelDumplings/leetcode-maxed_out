// prob404: Sum of Left Leaves

/*
 * Find the sum of all left leaves in a given binary tree.
 */

/*
 * Example:
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
 */

#include "include/Node.h"

class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root) return 0;
        if(!(root -> left) && !(root -> right))
            return 1;
        int result = 0;
        _postOrder(root, result);
        return result;
    }

private:
    bool _postOrder(TreeNode* root, int& result)
    {
        if(!(root -> left) && !(root -> right))
            return true;
        if(root -> left)
        {
            if(_postOrder(root -> left, result))
                result += root -> left -> val;
        }
        if(root -> right)
            _postOrder(root -> right, result);
        return false;
    }
};
