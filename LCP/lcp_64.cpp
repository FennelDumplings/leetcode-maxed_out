/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
状态设计
dp[s] := 当前的状态为 s 时，使得 u 子树全部熄灭所需的最少次数
            其中 s 状态共有 4 种
            s = 0:  子树 u 全都灭
            s = 1:  子树 u 全都亮
            s = 2:  子树 u 的根亮，其余节点全都灭
            s = 3:  子树 u 的根灭，其余节点全都亮

答案
dp[root][0]

初始化
dp[null][0..3] = 0

状态转移

(1) u 灭，则:
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution1 {
public:
    int closeLampInTree(TreeNode* root) {
        vector<int> dp = _postOrder(root);
        return dp[0];
    }

    vector<int> _postOrder(TreeNode* node)
    {
        if(!node)
            return {0, 0, 0, 0};
        vector<int> dp(4, INT_MAX);
        vector<int> dp_left = _postOrder(node -> left);
        vector<int> dp_right = _postOrder(node -> right);

        if(node -> val == 1)
        {
            // 全灭
            dp[0] = min(dp[0], 1 + dp_left[0] + dp_right[0]); // 按法 2
            dp[0] = min(dp[0], 1 + dp_left[1] + dp_right[1]); // 按法 3
            dp[0] = min(dp[0], 1 + dp_left[2] + dp_right[2]); // 按法 4
            dp[0] = min(dp[0], 3 + dp_left[3] + dp_right[3]); // 按法 8
             // 全亮
            dp[1] = min(dp[1], dp_left[1] + dp_right[1]); // 按法 1
            dp[1] = min(dp[1], 2 + dp_left[0] + dp_right[0]); // 按法 5
            dp[1] = min(dp[1], 2 + dp_left[3] + dp_right[3]); // 按法 6
            dp[1] = min(dp[1], 2 + dp_left[2] + dp_right[2]); // 按法 7
            // u 亮，其余全灭
            dp[2] = min(dp[2], dp_left[0] + dp_right[0]); // 按法 1
            dp[2] = min(dp[2], 2 + dp_left[1] + dp_right[1]); // 按法 5
            dp[2] = min(dp[2], 2 + dp_left[2] + dp_right[2]); // 按法 6
            dp[2] = min(dp[2], 2 + dp_left[3] + dp_right[3]); // 按法 7
            // u 灭，其余全亮
            dp[3] = min(dp[3], 1 + dp_left[1] + dp_right[1]); // 按法 2
            dp[3] = min(dp[3], 1 + dp_left[0] + dp_right[0]); // 按法 3
            dp[3] = min(dp[3], 1 + dp_left[3] + dp_right[3]); // 按法 4
            dp[3] = min(dp[3], 3 + dp_left[2] + dp_right[2]); // 按法 8
        }
        else
        {
            // 全灭
            dp[0] = min(dp[0], dp_left[0] + dp_right[0]); // 按法 1
            dp[0] = min(dp[0], 2 + dp_left[1] + dp_right[1]); // 按法 5
            dp[0] = min(dp[0], 2 + dp_left[2] + dp_right[2]); // 按法 6
            dp[0] = min(dp[0], 2 + dp_left[3] + dp_right[3]); // 按法 7
            // 全亮
            dp[1] = min(dp[1], 1 + dp_left[1] + dp_right[1]); // 按法 2
            dp[1] = min(dp[1], 1 + dp_left[0] + dp_right[0]); // 按法 3
            dp[1] = min(dp[1], 1 + dp_left[3] + dp_right[3]); // 按法 4
            dp[1] = min(dp[1], 3 + dp_left[2] + dp_right[2]); // 按法 8
            // u 亮，其余全灭
            dp[2] = min(dp[2], 1 + dp_left[0] + dp_right[0]); // 按法 2
            dp[2] = min(dp[2], 1 + dp_left[1] + dp_right[1]); // 按法 3
            dp[2] = min(dp[2], 1 + dp_left[2] + dp_right[2]); // 按法 4
            dp[2] = min(dp[2], 3 + dp_left[3] + dp_right[3]); // 按法 8
            // u 灭，其余全亮
            dp[3] = min(dp[3], dp_left[1] + dp_right[1]); // 按法 1
            dp[3] = min(dp[3], 2 + dp_left[0] + dp_right[0]); // 按法 5
            dp[3] = min(dp[3], 2 + dp_left[3] + dp_right[3]); // 按法 6
            dp[3] = min(dp[3], 2 + dp_left[2] + dp_right[2]); // 按法 7
        }
        return dp;
    }
};


class Solution {
public:
    int closeLampInTree(TreeNode* root) {
        idx = unordered_map<TreeNode*, int>();
        idx[nullptr] = 0;
        get_idx(root);
        int n = idx.size();
        dp = vector<vector<vector<int>>>(n, vector<vector<int>>(2, vector<int>(2, -1)));
        return _preOrder(root, 0, 0);
    }

    unordered_map<TreeNode*, int> idx; // 节点的编号
    vector<vector<vector<int>>> dp;

    void get_idx(TreeNode* node)
    {
        int i = idx.size();
        idx[node] = i;
        if(node -> left)
            get_idx(node -> left);
        if(node -> right)
            get_idx(node -> right);
    }

    int _preOrder(TreeNode* node, int s1, int s2)
    {
        if(dp[idx[node]][s1][s2] != -1)
            return dp[idx[node]][s1][s2];
        if(!node)
            return dp[idx[node]][s1][s2] = 0;
        int res = INT_MAX;
        if(((node -> val) ^ s1 ^ s2) == 1)
        {
            int res2 = 1 + _preOrder(node -> left, 0, s2) + _preOrder(node -> right, 0, s2); // 按法 2
            int res3 = 1 + _preOrder(node -> left, 1, s2) + _preOrder(node -> right, 1, s2); // 按法 3
            int res4 = 1 + _preOrder(node -> left, 0, s2 ^ 1) + _preOrder(node -> right, 0, s2 ^ 1); // 按法 4
            int res8 = 3 + _preOrder(node -> left, 1, s2 ^ 1) + _preOrder(node -> right, 1, s2 ^ 1); // 按法 8
            res = min(res, res2);
            res = min(res, res3);
            res = min(res, res4);
            res = min(res, res8);
        }
        else
        {
            int res1 = _preOrder(node -> left, 0, s2) + _preOrder(node -> right, 0, s2); // 按法 1
            int res5 = 2 + _preOrder(node -> left, 0, s2 ^ 1) + _preOrder(node -> right, 0, s2 ^ 1); // 按法 5
            int res6 = 2 + _preOrder(node -> left, 1, s2) + _preOrder(node -> right, 1, s2); // 按法 6
            int res7 = 2 + _preOrder(node -> left, 1, s2 ^ 1) + _preOrder(node -> right, 1, s2 ^ 1); // 按法 7
            res = min(res, res1);
            res = min(res, res5);
            res = min(res, res6);
            res = min(res, res7);
        }
        return dp[idx[node]][s1][s2] = res;
    }
};
