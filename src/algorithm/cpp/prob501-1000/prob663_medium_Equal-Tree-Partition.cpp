// prob663: Equal Tree Partition

/*
 * Given a binary tree with n nodes, your task is to check if it's possible to partition the tree to
 * two trees which have the equal sum of values after removing exactly one edge on the original tree.
 */

/*
 * Example 1:
 * Input:
 *     5
 *    / \
 *   10 10
 *     /  \
 *    2   3
 * Output: True
 * Explanation:
 *     5
 *    /
 *   10
 * Sum: 15
 *    10
 *   /  \
 *  2    3
 * Sum: 15
 * Example 2:
 * Input:
 *     1
 *    / \
 *   2  10
 *     /  \
 *    2   20
 * Output: False
 * Explanation: You can't split the tree into two trees with equal sum after removing exactly one edge on the tree.
 */

/*
 * Note:
 * The range of tree node value is in the range of [-100000, 100000].
 * 1 <= n <= 10000
 */

#include "include/Node.h"
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool checkEqualTree(TreeNode* root) {
        if(!root) return false;
        unordered_set<int> setting;
        int sum = _postOrder(root, setting);
        if(!(sum & 1) && setting.find(sum / 2) != setting.end())
            return true;
        else
            return false;
    }

private:
    int _postOrder(TreeNode* root, unordered_set<int>& setting)
    {
        int sum_left = 0, sum_right = 0;
        if(root -> left)
        {
            sum_left = _postOrder(root -> left, setting);
            setting.insert(sum_left);
        }
        if(root -> right)
        {
            sum_right = _postOrder(root -> right, setting);
            setting.insert(sum_right);
        }

        int sum = sum_left + sum_right + root -> val;
        return sum;
    }
};
