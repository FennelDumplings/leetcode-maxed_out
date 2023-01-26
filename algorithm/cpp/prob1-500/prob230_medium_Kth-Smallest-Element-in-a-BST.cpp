// prob230: Kth Smallest Element in a BST

/*
 * Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
 */

/*
 * Example 1:
 * Input: root = [3,1,4,null,2], k = 1
 *    3
 *   / \
 *  1   4
 *   \
 *    2
 * Output: 1
 * Example 2:
 * Input: root = [5,3,6,2,4,null,null,1], k = 3
 *        5
 *       / \
 *      3   6
 *     / \
 *    2   4
 *   /
 *  1
 * Output: 3
 */

/*
 * Follow up:
 * What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
 */

#include "include/Node.h"

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int node_num = 0;
        int result = -1;
        _inOrder(root, node_num, result, k);
        return result;
    }

private:
    bool _inOrder(TreeNode* root, int& node_num, int& result, int k)
    {
        if(root -> left)
            if(_inOrder(root -> left, node_num, result, k))
                return true;
        ++node_num;
        if(node_num == k)
        {
            result = root -> val;
            return true;
        }
        if(root -> right)
            if(_inOrder(root -> right, node_num, result, k))
                return true;
        return false;
    }
};
