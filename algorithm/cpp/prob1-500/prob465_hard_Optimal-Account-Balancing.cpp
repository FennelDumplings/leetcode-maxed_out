// prob465: Optimal Account Balancing

/*
 * https://leetcode-cn.com/problems/optimal-account-balancing/
 */

#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> net_value; // mapping[i] := i 的净值
        for(vector<int> &e: transactions)
        {
            net_value[e[0]] += e[2];
            net_value[e[1]] -= e[2];
        }
        vector<int> vec;
        for(auto i: net_value)
            if(i.second != 0)
                vec.push_back(i.second);
        return dfs(vec, 0);
    }

private:
    int dfs(vector<int>& vec, int pos)
    {
        int n = vec.size();
        if(pos == n)
            return 0;
        if(vec[pos] == 0)
            return dfs(vec, pos + 1);
        int ans = INT_MAX / 2;
        for(int nxt = pos + 1; nxt < n; ++nxt)
        {
            if((vec[nxt] ^ vec[pos]) < 0)
            {
                // 用 nxt 将 pos 平衡掉
                int tmp = vec[nxt];
                vec[nxt] = vec[nxt] + vec[pos];
                ans = min(ans, 1 + dfs(vec, pos + 1));
                vec[nxt] = tmp;
            }
            if(vec[nxt] + vec[pos] == 0)
                break;
        }
        return ans;
    }
};
