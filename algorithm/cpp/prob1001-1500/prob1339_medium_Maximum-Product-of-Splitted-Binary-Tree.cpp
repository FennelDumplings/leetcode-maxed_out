// prob1339: Maximum Product of Splitted Binary Tree

/*
 * https://leetcode-cn.com/problems/maximum-product-of-splitted-binary-tree/
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(TreeNode* root) {
        if(!root) return 0;
        int id = 0;
        _postOrder(root, id);
        ll ans = 0;
        dfs(0, ans);
        return ans % MOD;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    vector<vector<int>> g; // 邻接表
    vector<ll> w; // 点权

    void dfs(int node_id, ll& ans)
    {
        for(int son_id: g[node_id])
        {
            ans = max(ans, (w[0] - w[son_id]) * w[son_id]);
            dfs(son_id, ans);
        }
    }

    int _postOrder(TreeNode* node, int& id)
    {
        int node_id = id;
        g.push_back({});
        w.push_back(0);
        if(node -> left)
        {
            int left_id = _postOrder(node -> left, ++id);
            g[node_id].push_back(left_id);
            w[node_id] += w[left_id];
        }
        if(node -> right)
        {
            int right_id = _postOrder(node -> right, ++id);
            g[node_id].push_back(right_id);
            w[node_id] += w[right_id];
        }
        w[node_id] += node -> val;
        return node_id;
    }
};
