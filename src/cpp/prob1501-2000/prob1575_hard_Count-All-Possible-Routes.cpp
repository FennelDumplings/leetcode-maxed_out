// prob1575: Count All Possible Routes

/*
 * https://leetcode-cn.com/problems/count-all-possible-routes/
 */


#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int n = locations.size();
        dp = vector<vector<int>>(n, vector<int>(fuel + 1, -1));
        return solve(locations, start, finish, fuel);
    }

private:
    vector<vector<int>> dp;
    const int MOD = 1e9 + 7;
    using ll = long long;

    int solve(const vector<int>& locations, int i, const int t, int k)
    {
        if(k < 0)
            return 0;
        if(dp[i][k] != -1)
            return dp[i][k];
        int n = locations.size();
        int ans = 0;
        if(i == t) ++ans;
        for(int j = 0; j < n; ++j)
        {
            if(i == j)
                continue;
            ans = ((ll)ans + solve(locations, j, t, k - abs(locations[i] - locations[j]))) % MOD;
        }
        return dp[i][k] = ans;
    }
};
