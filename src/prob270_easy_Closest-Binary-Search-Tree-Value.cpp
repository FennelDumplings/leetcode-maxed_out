// prob270: Closest Binary Search Tree Value

/*
 * Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.
 * Note:
 * Given target value is a floating point.
 * You are guaranteed to have only one unique value in the BST that is closest to the target.
 */

/*
 * Example:
 * Input: root = [4,2,5,1,3], target = 3.714286
 *
 *     4
 *    / \
 *   2   5
 *  / \
 * 1   3
 * Output: 4
 */

#include "include/Node.h"
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        double min_gap = abs(root -> val - target);
        int result = root -> val;
        _preOrder(root, target, min_gap, result);
        return result;
    }

private:
    void _preOrder(TreeNode* root, double target, double& min_gap, int& result)
    {
        if(!root) return;
        if(abs((double)(root -> val) - target) < min_gap)
        {
            result = root -> val;
            min_gap = abs((double)(root -> val) - target);
        }
        if(root -> val > target)
            _preOrder(root -> left, target, min_gap, result);
        else
            _preOrder(root -> right, target, min_gap, result);
    }
};

// 非递归中序
// 看 root->val > target > prev 是否成立
