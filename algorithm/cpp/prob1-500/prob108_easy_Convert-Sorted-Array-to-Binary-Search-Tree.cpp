// prob108: Convert Sorted Array to Binary Search Tree

/*
 * Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 * For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two
 * subtrees of every node never differ by more than 1.
 */

/*
 * Example:
 * Given the sorted array: [-10,-3,0,5,9],
 * One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
 *
 *       0
 *      / \
 *    -3   9
 *    /   /
 *  -10  5
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return nullptr;
        int n = nums.size();
        return _build(nums, 0, n - 1);
    }

private:
    TreeNode* _build(const vector<int>& nums, int left, int right)
    {
        if(left > right) return nullptr;
        if(left == right) return new TreeNode(nums[left]);

        int mid = left + (right - left) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        if(left <= mid - 1)
        {
            TreeNode *left_root = _build(nums, left, mid - 1);
            root -> left = left_root;
        }
        if(mid + 1 <= right)
        {
            TreeNode *right_root = _build(nums, mid + 1, right);
            root -> right = right_root;
        }
        return root;
    }
};
