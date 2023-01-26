// interview04.02: 最小高度树

/*
 * https://leetcode-cn.com/problems/minimum-height-tree-lcci/
 */

#include "../../include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return nullptr;
        int n = nums.size();
        return build(nums, 0, n - 1);
    }

private:
    TreeNode* build(const vector<int>& nums, int left, int right)
    {
        if(left == right)
            return new TreeNode(nums[left]);

        int mid = (left + right + 1) / 2;
        TreeNode* node = new TreeNode(nums[mid]);
        if(mid > left)
            node -> left = build(nums, left, mid - 1);
        if(mid < right)
            node -> right = build(nums, mid + 1, right);
        return node;
    }
};
