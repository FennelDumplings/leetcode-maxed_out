// prob968: Binary Tree Cameras

/*
 * Given a binary tree, we install cameras on the nodes of the tree. 
 * Each camera at a node can monitor its parent, itself, and its immediate children.
 * Calculate the minimum number of cameras needed to monitor all nodes of the tree.
 */

/*
 * Example 1:
 * Input: [0,0,null,0,0]
 * Output: 1
 * Explanation: One camera is enough to monitor all nodes if placed as shown.
 * Example 2:
 * Input: [0,0,null,0,null,0,null,null,0]
 * Output: 2
 * Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.
 */

/*
 * Note:
 * The number of nodes in the given tree will be in the range [1, 1000].
 * Every node has value 0.
 */

#include <vector>
#include <climits>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    // dp[root] := min(dp1[root], dp2[root])
    // dp1[root] := root选
    // dp2[root] := root不选，且监控到 root
    // dp3[root] := root不选，且监控不到root
    // dp1[root] = min(dp[root -> left], dp3[root -> left])
    //             + min(dp[root -> right], dp3[root -> right])
    //             + 1
    // dp2[root] = min(dp1[root -> left] + dp[root -> right],
    //                 dp1[root -> right] + dp[root -> left],
    // dp3[root] = dp2[root -> left] + dp2[root -> right]
    int minCameraCover(TreeNode* root) {
        if(!root) return 0;
        return _postOrder(root)[0];
    }

private:
    vector<int> _postOrder(TreeNode* root)
    {
        if(!root)
            return vector<int>({0, INT_MAX / 2, 0, 0});

        vector<int> dp(4, 0);
        vector<int> dp_left(4, 0);
        vector<int> dp_right(4, 0);

        dp_left = _postOrder(root -> left);
        dp_right = _postOrder(root -> right);

        dp[1] = min(dp_left[0], dp_left[3])
              + min(dp_right[0], dp_right[3])
              + 1;
        dp[2] = min(dp_left[1] + dp_right[0], dp_left[0] + dp_right[1]);
        dp[3] = dp_left[2] + dp_right[2];
        dp[0] = min(dp[1], dp[2]);

        return dp;
    }
};
