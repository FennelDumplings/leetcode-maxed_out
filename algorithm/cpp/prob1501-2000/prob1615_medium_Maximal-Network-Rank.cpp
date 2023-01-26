// prob1615: Maximal Network Rank

/*
 * https://leetcode-cn.com/problems/maximal-network-rank/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        // adj[i][j] := i,j 直接相连的条数
        vector<vector<int>> adj(n, vector<int>(n, 0));
        for(const vector<int> &e: roads)
        {
            ++adj[e[0]][e[1]];
            ++adj[e[1]][e[0]];
        }
        int ans = 0;
        vector<int> col_sum(n), row_sum(n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
            {
                col_sum[j] += adj[i][j];
                row_sum[i] += adj[i][j];
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(i == j)
                    continue;
                ans = max(ans, row_sum[i] + col_sum[j] - adj[i][j]);
            }
        return ans;
    }
};
