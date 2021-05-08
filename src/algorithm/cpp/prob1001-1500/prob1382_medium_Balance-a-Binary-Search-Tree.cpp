// prob1382: Balance a Binary Search Tree

/*
 * Given a binary search tree, return a balanced binary search tree with the same node values.
 * A binary search tree is balanced if and only if the depth of the two subtrees of every node never differ by more than 1.
 * If there is more than one answer, return any of them.
 */

/*
 * Example 1:
 * Input: root = [1,null,2,null,3,null,4,null,null]
 * Output: [2,1,3,null,null,null,4]
 * Explanation: This is not the only correct answer, [3,1,4,null,2,null,null] is also correct.
 */

/*
 * Constraints:
 * The number of nodes in the tree is between 1 and 10^4.
 * The tree nodes will have distinct values between 1 and 10^5.
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    // 中序遍历的结果存在一个数组中，然后调用 Prob 108
    TreeNode* balanceBST(TreeNode* root) {
        if(!root) return nullptr;
        vector<int> vec;
        _inOrder(root, vec);
        Solution_prob108 sulution;
        return sulution.sortedArrayToBST(vec);
    }

private:
    void _inOrder(TreeNode* root, vector<int>& vec)
    {
        if(root -> left)
            _inOrder(root -> left, vec);
        vec.push_back(root -> val);
        if(root -> right)
            _inOrder(root -> right, vec);
    }

    class Solution_prob108 {
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
};

// 手撕平衡树并没有用到 BST 的性质，效率偏低，但通用，非 BST 也可以使用
// https://leetcode-cn.com/problems/balance-a-binary-search-tree/solution/shou-si-avlshu-wo-bu-guan-wo-jiu-shi-yao-xuan-zhua/
