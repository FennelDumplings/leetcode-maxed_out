
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;


class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        int n = cost.size();
        int m = cost[0].size();
        dp = unordered_map<int, int>();
        dp[(1 << (n + m)) - 1] = 0;
        int start = 0;
        return solve(start, cost);
    }

private:
    // dp[s] := 已经联通了 s 这些点，后续的最小成本
    unordered_map<int, int> dp;

    int solve(int& s, const vector<vector<int>>& cost)
    {
        int n = cost.size();
        int m = cost[0].size();
        //cout << s << endl;
        if(dp.count(s))
            return dp[s];
        dp[s] = -1;
        int &ans = dp[s];
        for(int i = 0; i < n; ++i)
        {
            if((s >> i) & 1)
            {
                // i 选过
                for(int j = 0; j < m; ++j)
                {
                    if((s >> (n + j)) & 1)
                        continue;
                    // 连接 i, j
                    s |= (1 << (n + j));
                    if(ans == -1)
                        ans = cost[i][j] + solve(s, cost);
                    else
                        ans = min(ans, cost[i][j] + solve(s, cost));
                    s &= ~(1 << (n + j));
                }
            }
            else
            {
                // i 尚未选过
                s |= (1 << i);
                for(int j = 0; j < m; ++j)
                {
                    // 连接 i, j
                    bool flag = (s >> (n + j)) & 1;
                    if(!flag)
                        s |= (1 << (n + j));
                    if(ans == -1)
                        ans = cost[i][j] + solve(s, cost);
                    else
                        ans = min(ans, cost[i][j] + solve(s, cost));
                    if(!flag)
                        s &= ~(1 << (n + j));
                }
                s &= ~(1 << i);
            }
        }
        return ans;
    }
};
