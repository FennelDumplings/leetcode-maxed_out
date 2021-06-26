// prob250: Count Univalue Subtrees

/*
 * Given a binary tree, count the number of uni-value subtrees.
 * A Uni-value subtree means all nodes of the subtree have the same value.
 */

/*
 * Example :
 * Input:  root = [5,1,5,5,5,null,5]
 *               5
 *              / \
 *             1   5
 *            / \   \
 *           5   5   5
 *
 * Output: 4
 */

#include "include/Node.h"

class Solution {
public:
    int countUnivalSubtrees(TreeNode* root) {
        if(!root) return 0;
        int result = 0;
        _postOrder(root, result);
        return result;
    }

private:
    bool _postOrder(TreeNode* root, int& result)
    {
        bool same = true;
        if(root -> left)
        {
            same = _postOrder(root -> left, result) && same;
            same = same && (root -> val == root -> left -> val);
        }
        if(root -> right)
        {
            same = _postOrder(root -> right, result) && same;
            same = same && (root -> val == root -> right -> val);
        }

        if(same) ++result;
        return same;
    }
};
