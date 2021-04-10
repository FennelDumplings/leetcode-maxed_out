/**
 * Definition for a binary tree node.
 */

#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxValue(TreeNode* root, int k) {
        int root_id = build_adjlist(root);
        int n = w.size();
        dp = vector<vector<int>>(n, vector<int>(k + 1, -1));
        max_val = vector<int>(n, -1);
        dfs(root_id, k);
        return max_val[root_id];
    }

private:
    vector<vector<int>> g;
    vector<int> w;
    vector<vector<int>> dp; // dp[u][k] := 以 u 为根，且与 u 相连的蓝有 k 个时，最大分数
    vector<int> max_val;

    void dfs(int u, const int k)
    {
        if(g[u].empty())
        {
            // 叶子节点
            dp[u][0] = 0;
            dp[u][1] = w[u];
            max_val[u] = w[u];
            return;
        }
        for(int v: g[u])
            dfs(v, k);
        // 根不置蓝 dp[u][0]
        dp[u][0] = 0;
        for(int v: g[u])
            dp[u][0] += max_val[v];
        // 根置蓝 dp[u][j]
        if(g[u].size() == 1)
        {
            // 只有一个子节点
            for(int j = 1; j <= k; ++j)
            {
                // 计算 dp[u][j], 根节点占一个
                int left = j - 1;
                if(dp[g[u][0]][left] != -1)
                    dp[u][j] = dp[g[u][0]][left] + w[u];
            }
        }
        else
        {
            // 有两个子节点
            for(int j = 1; j <= k; ++j)
            {
                // 计算 dp[u][j], 根节点占一个
                for(int left = 0; left <= j - 1; ++left)
                {
                    int right = j - 1 - left;
                    if(dp[g[u][0]][left] != -1 && dp[g[u][1]][right] != -1)
                        dp[u][j] = max(dp[u][j], dp[g[u][0]][left] + dp[g[u][1]][right] + w[u]);
                }
            }
        }

        max_val[u] = 0;
        for(int j = 0; j <= k; ++j)
            max_val[u] = max(max_val[u], dp[u][j]);
    }

    int build_adjlist(TreeNode* node)
    {
        g.push_back({});
        w.push_back(node -> val);
        int node_id = g.size() - 1;
        if(node -> left)
        {
            int left_id = build_adjlist(node -> left);
            g[node_id].push_back(left_id);
        }
        if(node -> right)
        {
            int right_id = build_adjlist(node -> right);
            g[node_id].push_back(right_id);
        }
        return node_id;
    }
};
