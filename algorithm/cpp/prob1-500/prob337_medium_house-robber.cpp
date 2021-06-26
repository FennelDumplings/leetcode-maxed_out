// prob337: house-robber

/*
 * The thief has found himself a new place for his thievery again. There is only one entrance to this area,
 * called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart
 * thief realized that "all houses in this place forms a binary tree". It will automatically contact the
 * police if two directly-linked houses were broken into on the same night.
 * Determine the maximum amount of money the thief can rob tonight without alerting the police.
 */

/*
 * Example 1:
 * Input: [3,2,3,null,3,null,1]
 *      3
 *     / \
 *    2   3
 *     \   \
 *      3   1
 * Output: 7
 * Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
 * Example 2:
 * Input: [3,4,5,1,3,null,1]
 *      3
 *     / \
 *    4   5
 *   / \   \
 *  1   3   1
 * Output: 9
 * Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
 */

#include "include/Node.h"
#include <vector>

using namespace std;

struct Node {
    int max1; // 选当前点的最大值
    int max2; // 不选当前点的最大值
    Node(int a=0, int b=0)
    {
        max1 = a;
        max2 = b;
    }
};

class Solution {
public:
    int rob(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        dfs(root, ans);
        return ans;
    }

private:
    Node dfs(TreeNode* root, int& ans)
    {
        Node node, left, right;
        node.max1 = root -> val;
        if(root -> left)
            left = dfs(root -> left, ans);
        if(root -> right)
            right = dfs(root -> right, ans);
        node.max1 += left.max2 + right.max2;
        node.max2 += max(left.max1, left.max2) + max(right.max1, right.max2);
        ans = max(ans, node.max1);
        ans = max(ans, node.max2);
        return node;
    }
};
