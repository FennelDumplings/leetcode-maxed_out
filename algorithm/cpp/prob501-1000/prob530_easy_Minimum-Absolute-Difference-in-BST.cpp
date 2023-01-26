// prob539: Minimum Absolute Difference in BST

/*
 * Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.
 */

/*
 * Example:
 * Input:
 *    1
 *     \
 *      3
 *     /
 *    2
 * Output:
 * 1
 * Explanation:
 * The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
 */

/*
 * Note:
 * There are at least two nodes in this BST.
 * This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/
 */

#include <climits>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int result = INT_MAX;;
        TreeNode *prev = nullptr;
        _inOrder(root, prev, result);
        return result;
    }

private:
    void _inOrder(TreeNode* root, TreeNode*& prev, int& result)
    {
        if(root -> left)
        {
            _inOrder(root -> left, prev, result);
        }

        if(prev)
        {
            int gap = root -> val - prev -> val;
            if(gap < result)
                result = gap;
        }
        prev = root;

        if(root -> right)
        {
            _inOrder(root -> right, prev, result);
        }
    }
};
