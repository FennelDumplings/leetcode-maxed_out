// prob298: Binary Tree Longest Consecutive Sequence

/*
 * ven a binary tree, find the length of the longest consecutive sequence path.
 * The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections.
 * The longest consecutive path need to be from parent to child (cannot be the reverse).
 */

/*
 * Example 1:
 * Input:
 *    1
 *     \
 *      3
 *     / \
 *    2   4
 *         \
 *          5
 * Output: 3
 * Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
 * Example 2:
 * Input:
 *    2
 *     \
 *      3
 *     /
 *    2
 *   /
 *  1
 * Output: 2
 * Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return 2.
 */

#include <vector>
#include <climits>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        if(!root) return 0;
        int result = INT_MIN;
        _postOrder(root, result);
        return result;
    }

private:
    int _postOrder(TreeNode* root, int& result)
    {
        int len_left = 0, len_right = 0;
        int len = 1;
        if(root -> left)
        {
            len_left = _postOrder(root -> left, result);
            if(root -> val + 1 == root -> left -> val)
                len = max(len, len_left + 1);
        }
        if(root -> right)
        {
            len_right = _postOrder(root -> right, result);
            if(root -> val + 1 == root -> right -> val)
                len = max(len, len_right + 1);
        }
        result = max(result, len);
        return len;
    }
};
