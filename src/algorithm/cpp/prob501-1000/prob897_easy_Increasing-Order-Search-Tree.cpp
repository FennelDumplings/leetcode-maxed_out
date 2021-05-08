// prob897: Increasing Order Search Tree

/*
 * Given a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree,
 * and every node has no left child and only 1 right child.
 */

/*
 * Example 1:
 * Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]
 *        5
 *       / \
 *     3    6
 *    / \    \
 *   2   4    8
 *  /        / \
 * 1        7   9
 * Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
 *  1
 *   \
 *    2
 *     \
 *      3
 *       \
 *        4
 *         \
 *          5
 *           \
 *            6
 *             \
 *              7
 *               \
 *                8
 *                 \
 *                  9
 */

/*
 * Constraints:
 * The number of nodes in the given tree will be between 1 and 100.
 * Each node will have a unique integer value from 0 to 1000.
 */

#include "include/Node.h"

/*
 * 给你一棵二叉搜索树，请你 按中序遍历 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。
 */

class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode *precursor = nullptr;
        TreeNode *result = nullptr;
        _inOrder(root, precursor, result);
        return result;
    }

private:
    void _inOrder(TreeNode* node, TreeNode*& precursor, TreeNode*& result)
    {
        if(node -> left)
            _inOrder(node -> left, precursor, result);

        if(!precursor)
            result = node;
        else
            precursor -> right = node;
        precursor = node;
        precursor -> left = nullptr;

        if(node -> right)
            _inOrder(node -> right, precursor, result);
    }
};
