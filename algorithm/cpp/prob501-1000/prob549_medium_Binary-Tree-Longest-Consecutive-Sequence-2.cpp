// prob549: Binary Tree Longest Consecutive Sequence II

/*
 onsidered valid, but the path [1,2,4,3] is not valid. On the other hand, the path can be in the child-Parent-child order,
 where not necessarily be parent-child order.
 /

/*
 * Example 1:
 * Input:
 *         1
 *        / \
 *       2   3
 * Output: 2
 * Explanation: The longest consecutive path is [1, 2] or [2, 1].
 * Example 2:
 * Input:
 *         2
 *        / \
 *       1   3
 * Output: 3
 * Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
 */

/*
 * Note: All the values of tree nodes are in the range of [-1e7, 1e7].
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        _postOrder(root, ans);
        return ans;
    }

private:
    using PII = pair<int, int>;

    PII _postOrder(TreeNode* root, int& ans)
    {
        // PII 从子树根开始的递减序列长，递增序列长
        PII result_left({0, 0}), result_right({0, 0});
        if(root -> left)
            result_left = _postOrder(root -> left, ans);
        if(root -> right)
            result_right = _postOrder(root -> right, ans);

        int cur = root -> val;
        PII result({1, 1});
        bool left_less = false, left_greater = false;
        bool right_less = false, right_greater = false;
        if(root -> left)
        {
            if(cur - 1 == root -> left -> val)
                left_less = true;
            if(cur + 1 == root -> left -> val)
                left_greater = true;
        }
        if(root -> right)
        {
            if(cur - 1 == root -> right -> val)
                right_less = true;
            if(cur + 1 == root -> right -> val)
                right_greater = true;
        }
        if(left_less) result.first = max(result.first, 1 + result_left.first);
        if(right_less) result.first = max(result.first, 1 + result_right.first);
        if(left_greater) result.second = max(result.second, 1 + result_left.second);
        if(right_greater) result.second = max(result.second, 1 + result_right.second);
        ans = max(ans, max(result.first, result.second));
        if(left_less && right_greater) ans = max(ans, result_left.first + 1 + result_right.second);
        if(left_greater && right_less) ans = max(ans, result_left.second + 1 + result_right.first);
        return result;
    }
};
