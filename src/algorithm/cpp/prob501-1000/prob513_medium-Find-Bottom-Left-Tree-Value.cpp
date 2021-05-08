// prob513: Find Bottom Left Tree Value

/*
 * Given a binary tree, find the leftmost value in the last row of the tree.
 */

/*
 * Example 1:
 * Input:
 *     2
 *    / \
 *   1   3
 * Output:
 * 1
 * Example 2:
 * Input:
 *         1
 *        / \
 *       2   3
 *      /   / \
 *     4   5   6
 *        /
 *       7
 * Output:
 * 7
 * Note: You may assume the tree (i.e., the given root node) is not NULL.
 */

#include "include/Node.h"

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if(!root) return 0;
        int result = root -> val;
        int max_level = 0;
        _preOrder(root, 1, result, max_level);
        return result;
    }

private:
    void _preOrder(TreeNode* root, int level, int& result, int& max_level)
    {
        if(level > max_level)
        {
            result = root -> val;
            max_level = level;
        }

        if(root -> left)
        {
            _preOrder(root -> left, level + 1, result, max_level);
        }
        if(root -> right)
        {
            _preOrder(root -> right, level + 1, result, max_level);
        }
    }
};
