using ll = long long;

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        int n = robot.size();
        vector<int> fac_pos;
        for(const vector<int>& fac: factory)
        {
            for(int i = 0; i < fac[1]; ++i)
                fac_pos.push_back(fac[0]);
        }
        int m = fac_pos.size();
        vector<vector<ll>> d(n, vector<ll>(m));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                d[i][j] = abs(robot[i] - fac_pos[j]);
            }

        // dp[i][j] := robot[0..i] 由 factory[0..j] 负责，最短距离和。需要 i <= j
        vector<vector<ll>> dp(n, vector<ll>(m));
        dp[0][0] = d[0][0];
        for(int i = 1; i < n; ++i)
            dp[i][i] = dp[i - 1][i - 1] + d[i][i];
        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j < m; ++j)
            {
                dp[i][j] = dp[i][j - 1];
                if(i > 0)
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + d[i][j]);
                else
                    dp[i][j] = min(dp[i][j], d[i][j]);
            }
        }
        return dp[n - 1][m - 1];
    }
};
