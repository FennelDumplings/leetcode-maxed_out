// prob687: Longest Univalue Path

/*
 * Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.
 * The length of path between two nodes is represented by the number of edges between them.
 */

/*
 * Example 1:
 * Input:
 *
 *               5
 *              / \
 *             4   5
 *            / \   \
 *           1   1   5
 * Output: 2
 * Example 2:
 * Input:
 *               1
 *              / \
 *             4   5
 *            / \   \
 *           4   4   5
 * Output: 2
 */

/*
 * Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        if(!root) return 0;
        int result = 0;
        _postOrder(root, result);
        return result - 1;
    }

private:
    int _postOrder(TreeNode* root, int& result)
    {
        int len = 1, root_result = 1;;
        int len_left = 0, len_right = 0;
        if(root -> left)
        {
            len_left = _postOrder(root -> left, result);
            if(root -> val == root -> left -> val)
            {
                root_result += len_left;
                len = max(len, len_left + 1);
            }
        }
        if(root -> right)
        {
            len_right = _postOrder(root -> right, result);
            if(root -> val == root -> right -> val)
            {
                root_result += len_right;
                len = max(len, len_right + 1);
            }
        }

        result = max(result, root_result);
        return len;
    }
};
