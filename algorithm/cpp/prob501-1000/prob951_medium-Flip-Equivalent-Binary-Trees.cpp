// prob951: Flip Equivalent Binary Trees

/*
 * For a binary tree T, we can define a flip operation as follows: choose any node, and swap the left and right child subtrees.
 * A binary tree X is flip equivalent to a binary tree Y if and only if we can make X equal to Y after some number of flip operations.
 * Write a function that determines whether two binary trees are flip equivalent.  The trees are given by root nodes root1 and root2.
 */

/*
 * Example 1:
 * Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
 * Output: true
 * Explanation: We flipped at nodes with values 1, 3, and 5.
 */

/*
 * Note:
 * Each tree will have at most 100 nodes.
 * Each value in each tree will be a unique integer in the range [0, 99].
 */

#include "include/Node.h"

class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;
        if(root1 -> val != root2 -> val)
            return false;
        return _preOrder(root1, root2);
    }

private:
    bool _preOrder(TreeNode* root1, TreeNode* root2)
    {
        // 调用方保证 root1 -> val == root2 -> val;
        if(root1 -> left && root1 -> right && root2 -> left && root2 -> right)
        {
            // root1 和 root2 均有两个子节点
            if(root1 -> left -> val == root2 -> left -> val && root1 -> right -> val == root2 -> right -> val)
                if(_preOrder(root1 -> left, root2 -> left) && _preOrder(root1 -> right, root2 -> right))
                    return true;
            if(root1 -> left -> val == root2 -> right -> val && root1 -> left -> val == root2 -> right -> val)
                if(_preOrder(root1 -> left, root2 -> right) && _preOrder(root1 -> right, root2 -> left))
                    return true;
            return false;
        }
        else if(!root1 -> left && !root1 -> right && !root2 -> left && !root2 -> right)
            // root1 和 root2 均有 0 个子节点
            return true;
        else if(!root1 -> left && !root2 -> left && root1 -> right && root2 -> right)
        {
            if(root1 -> right -> val == root2 -> right -> val)
                if(_preOrder(root1 -> right, root2 -> right))
                    return true;
            return false;
        }
        else if(!root1 -> right && !root2 -> right && root1 -> left && root2 -> left)
        {
            if(root1 -> left -> val == root2 -> left -> val)
                if(_preOrder(root1 -> left, root2 -> left))
                    return true;
            return false;
        }
        else if(!root1 -> right && !root2 -> left && root1 -> left && root2 -> right)
        {
            if(root1 -> left -> val == root2 -> right -> val)
                if(_preOrder(root1 -> left, root2 -> right))
                    return true;
            return false;
        }
        else if(!root1 -> left && !root2 -> right && root1 -> right && root2 -> left)
        {
            if(root1 -> right -> val == root2 -> left -> val)
                if(_preOrder(root1 -> right, root2 -> left))
                    return true;
            return false;
        }
        return false;
    }
};
