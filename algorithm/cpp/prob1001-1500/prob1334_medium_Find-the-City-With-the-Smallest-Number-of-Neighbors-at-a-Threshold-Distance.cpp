// prob1334: Find the City With the Smallest Number of Neighbors at a Threshold Distance

/*
 * https://leetcode-cn.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX / 2));
        for(const vector<int>& edge: edges)
        {
            dp[edge[0]][edge[1]] = edge[2];
            dp[edge[1]][edge[0]] = edge[2];
        }
        for(int i = 0; i < n; ++i)
            dp[i][i] = 0;
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        int min_neighbor = n;
        int ans = n;
        for(int i = n - 1; i >= 0; --i)
        {
            int cnt = 0;
            for(int j = 0; j < n; ++j)
            {
                if(j == i) continue;
                if(dp[i][j] <= distanceThreshold)
                    ++cnt;
            }
            if(cnt < min_neighbor)
            {
                min_neighbor = cnt;
                ans = i;
            }
        }
        return ans;
    }
};
