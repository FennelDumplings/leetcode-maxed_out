// prob654: Maximum Binary Tree

/*
 * Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:
 * 1. The root is the maximum number in the array.
 * 2. The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
 * 3. The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
 * Construct the maximum tree by the given array and output the root node of this tree.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <vector>
#include <stack>
#include "include/Node.h"

using namespace std;

// stack<TreeNode*>
// 进栈时候，栈内一些元素因为比进栈元素小而弹出
// 先弹出元素是后弹出元素的右子树根, 最后弹出元素是进栈元素的左子树根
class Solution1 {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.empty()) return nullptr;
        int n = nums.size();
        stack<TreeNode*> st;
        for(int i = 0; i < n; ++i)
        {
            TreeNode *iter = new TreeNode(nums[i]);
            if(st.empty() || st.top() -> val > nums[i])
                st.push(iter);
            else
            {
                TreeNode *st_top = st.top();
                st.pop();
                while(!st.empty() && st.top() -> val < nums[i])
                {
                    st.top() -> right = st_top;
                    st_top = st.top();
                    st.pop();
                }
                iter -> left = st_top;
                st.push(iter);
            }
        }
        TreeNode *result = st.top();
        st.pop();
        while(!st.empty())
        {
            st.top() -> right = result;
            result = st.top();
            st.pop();
        }
        return result;
    }
};

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.empty()) return nullptr;
        int n = nums.size();
        TreeNode *result = build_tree(nums, 0, n - 1);
        return result;
    }

    TreeNode* build_tree(const vector<int>& nums, int left, int right)
    {
        if(left > right)
        {
            return nullptr;
        }
        int max_idx = -1;
        int max_num = -1;
        for(int i = left; i <= right; ++i)
        {
            if(nums[i] > max_num)
            {
                max_num = nums[i];
                max_idx = i;
            }
        }
        TreeNode *result = new TreeNode(max_num);
        result -> left = build_tree(nums, left, max_idx - 1);
        result -> right = build_tree(nums, max_idx + 1, right);
        return result;
    }
};
