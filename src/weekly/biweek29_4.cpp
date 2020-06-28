// 20200627
// 4.

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        vector<vector<int> > g(n + 1);
        vector<int> indegrees(n + 1, 0);
        for(vector<int> &dependency: dependencies)
        {
            g[dependency[0]].push_back(dependency[1]);
            ++indegrees[dependency[1]];
        }

        vector<int> dp(1 << n, -1); // dp[state] := 选中情况为 state 时的最少天数
        dp[(1 << n) - 1] = 0;
        // dp[state] := dp[state'] + 1 其中 state' 为 state 增加若干门课
        vector<int> q;
        for(int i = 1; i <= n; ++i)
            if(indegrees[i] == 0)
                q.push_back(i);
        // cout << q.size() << endl;
        return solve(g, indegrees, q, 0, dp, k);
    }

private:
    int solve(const vector<vector<int> >& g, vector<int> indegrees, vector<int> q, int state, vector<int>& dp, int K)
    {
        if(dp[state] != -1)
            return dp[state];
        dp[state] = g.size();
        // 当前候选 q;
        int n_cand = q.size();
        if(n_cand <= K)
        {
            // 所有 q 都选
            int add_state = 0;
            vector<int> new_indegrees = indegrees;
            vector<int> new_nodes;
            for(int node: q)
            {
                add_state |= (1 << (node - 1));
                for(int son: g[node])
                {
                    --new_indegrees[son];
                    if(new_indegrees[son] == 0)
                        new_nodes.push_back(son);
                }
            }
            // cout << new_nodes.size() << endl;
            dp[state] = min(dp[state], 1 + solve(g, new_indegrees, new_nodes, state | add_state, dp, K));
            return dp[state];
        }
        // n_cand 中选 K 个
        // [0..n_cand] 选 k 个
        // cout << n_cand << " " << K << endl;
        vector<vector<int>> com = combine(n_cand, K);
        for(vector<int>& selects: com)
        {
            // cout << "[[[]]]" << endl;
            int add_state = 0;
            vector<int> new_indegrees = indegrees;
            vector<int> new_nodes;
            vector<bool> selected(n_cand, false);
            for(int idx: selects)
            {
                selected[idx - 1] = true;
                int node = q[idx - 1];
                add_state |= (1 << (node - 1));
                for(int son: g[node])
                {
                    --new_indegrees[son];
                    if(new_indegrees[son] == 0)
                        new_nodes.push_back(son);
                }
            }
            for(int i = 0; i < n_cand; ++i)
                if(!selected[i])
                    new_nodes.push_back(q[i]);
            dp[state] = min(dp[state], 1 + solve(g, new_indegrees, new_nodes, state | add_state, dp, K));
        }
        return dp[state];
    }

    vector<vector<int>> combine(int n, int k) {
        // 返回 [1..n] 中的 k 个
        vector<int> nums(k, 0);
        for(int i = 1; i <= k; ++i)
            nums[i - 1] = i;
        nums.push_back(n + 1); // 哨兵

        vector<vector<int> > results;
        int j = 0;
        while(j < k)
        {
            results.push_back(vector<int>(nums.begin(), nums.begin() + k));
            j = 0;
            while(j < k && nums[j + 1] == nums[j] + 1)
            {
                nums[j] = j + 1;
                ++j;
            }
            ++nums[j];
        }
        return results;
    }
};

