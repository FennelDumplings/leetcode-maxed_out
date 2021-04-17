// prob563: Binary Tree Tilt

/*
 * Given a binary tree, return the tilt of the whole tree.
 * The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node
 * values and the sum of all right subtree node values. Null node has tilt 0.
 * The tilt of the whole tree is defined as the sum of all nodes' tilt.
 */

/*
 * Example:
 * Input:
 *          1
 *        /   \
 *       2     3
 * Output: 1
 * Explanation:
 * Tilt of node 2 : 0
 * Tilt of node 3 : 0
 * Tilt of node 1 : |2-3| = 1
 * Tilt of binary tree : 0 + 0 + 1 = 1
 */

/*
 * The sum of node values in any subtree won't exceed the range of 32-bit integer.
 * All the tilt values won't exceed the range of 32-bit integer.
 */

#include <cmath>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int findTilt(TreeNode* root) {
        if(!root) return 0;
        int result = 0;
        _postOrder(root, result);
        return result;
    }

private:
    int _postOrder(TreeNode* root, int& result)
    {
        int sum_left = 0, sum_right = 0;
        if(root -> left)
            sum_left = _postOrder(root -> left, result);
        if(root -> right)
            sum_right = _postOrder(root -> right, result);

        int degree = abs(sum_left - sum_right);
        result += degree;
        return sum_left + sum_right + root -> val;
    }
};
