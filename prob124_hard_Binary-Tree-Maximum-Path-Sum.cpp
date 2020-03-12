// prob124: Binary Tree Maximum Path Sum

/*
 * Given a non-empty binary tree, find the maximum path sum.
 * For this problem, a path is defined as any sequence of nodes from some starting node to any
 * node in the tree along the parent-child connections. The path must contain at least one
 * node and does not need to go through the root.
 */

#include <climits>
#include <algorithm>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int result = INT_MIN;
        _postOrder(root, result);
        return result;
    }

private:
    int _postOrder(TreeNode* root, int& result)
    {
        int max_root = root -> val;
        int max_child = INT_MIN;
        int max_left = INT_MIN, max_right = INT_MIN;
        if(root -> left)
        {
            max_left = _postOrder(root -> left, result);
            max_root = max(max_root, root -> val + max_left);
            max_child = max(max_child, max_left);
        }
        if(root -> right)
        {
            max_right = _postOrder(root -> right, result);
            max_root = max(max_root, root -> val + max_right);
            max_child = max(max_child, max_right);
        }
        if(root -> left && root -> right)
            max_child = max(max_child, max_left + max_right + root -> val);
        result = max(result, max(max_root, max_child));
        return max_root;
    }
};

