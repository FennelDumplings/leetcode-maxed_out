// prob814: Binary Tree Pruning

/*
 * We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.
 * Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
 * (Recall that the subtree of a node X is X, plus every node that is a descendant of X.)
 */

/*
 * Example 1:
 * Input: [1,null,0,0,1]
 * Output: [1,null,0,null,1]
 * Explanation:
 * Only the red nodes satisfy the property "every subtree not containing a 1".
 * The diagram on the right represents the answer.
 * Example 2:
 * Input: [1,0,1,0,0,0,1]
 * Output: [1,null,1,null,1]
 * Example 3:
 * Input: [1,1,0,1,1,0,1,0]
 * Output: [1,1,0,1,1,null,1]
 */

/*
 * Note:
 * The binary tree will have at most 100 nodes.
 * The value of each node will only be 0 or 1.
 */

#include "include/Node.h"

class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if(!root) return nullptr;
        if(_postOrder(root))
            return root;
        else
            return nullptr;
    }

private:
    bool _postOrder(TreeNode* root)
    {
        if(root -> left)
        {
            bool result_left = _postOrder(root -> left);
            if(!result_left)
                root -> left = nullptr;
        }
        if(root -> right)
        {
            bool result_right = _postOrder(root -> right);
            if(!result_right)
                root -> right = nullptr;
        }
        if(root -> val == 0 && !(root -> left) && !(root -> right))
            return false;
        else
            return true;
    }
};
