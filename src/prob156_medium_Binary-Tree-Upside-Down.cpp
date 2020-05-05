// prob156: Binary Tree Upside Down

/*
 * Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares
 * the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned
 * into left leaf nodes. Return the new root.
 */

/*
 * Example:
 * Input: [1,2,3,4,5]
 *     1
 *    / \
 *   2   3
 *  / \
 * 4   5
 * Output: return the root of the binary tree [4,5,2,#,#,3,1]
 *    4
 *   / \
 *  5   2
 *     / \
 *    3   1
 */

#include "include/Node.h"

class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if(!root) return nullptr;
        TreeNode *result = dfs(root);
        return result;
    }

private:
    TreeNode* dfs(TreeNode* root)
    {
        if(!(root -> left))
            return root;
        TreeNode* result = dfs(root -> left);
        root -> left -> right = root;
        if(root -> right)
            root -> left -> left = root -> right;
        root -> left = nullptr;
        if(root -> right)
            root -> right = nullptr;
        return result;
    }
};
