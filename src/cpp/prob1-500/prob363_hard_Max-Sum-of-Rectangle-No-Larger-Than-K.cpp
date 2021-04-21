// prob363: Max Sum of Rectangle No Larger Than K

/*
 * Given a non-empty 2D matrix matrix and an lleger k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.
 */

/*
 * Example:
 * Input: matrix = [[1,0,1],[0,-2,3]], k = 2
 * Output: 2
 * Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
 *              and 2 is the max number no larger than k (k = 2).
 */

/*
 * Note:
 * The rectangle inside the matrix must have an area > 0.
 * What if the number of rows is much larger than the number of columns?
 */

#include <vector>
#include <climits>

using namespace std;

using ll = long long;

class Solution {
public:
    ll maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if(matrix.empty()) return 0;
        ll n = matrix.size(), m = matrix[0].size();
        vector<vector<ll>> sums(n + 1, vector<ll>(m + 1, 0));
        for(ll i = 1; i <= n; ++i)
            for(ll j = 1; j <= m; ++j)
                sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i - 1][j - 1];
        vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(m, vector<ll>(m + 1, INT_MIN)));
        // dp[i][j][l] := 以 (i, j) 为右下角，宽度为 l 的最大矩形和
        ll ans = INT_MIN;
        dp[0][0][1] = matrix[0][0];
        if(dp[0][0][1] <= k)
            ans = dp[0][0][1];
        // dp[0][j][1..j+1]
        for(ll j = 1; j < m; ++j)
            for(ll l = 1; l <= j + 1; ++l)
            {
                dp[0][j][l] = rec_sum(0, j, 0, j - l + 1, sums);
                if(dp[0][j][l] <= k)
                    ans = max(ans, dp[0][j][l]);
            }
        // dp[i][0][1]
        for(ll i = 1; i < n; ++i)
        {
            dp[i][0][1] = matrix[i][0] + max(dp[i - 1][0][1], (ll)0);
            if(dp[i][0][1] <= k)
                ans = max(ans, dp[i][0][1]);
            else
            {
                for(ll ii = i - 1; ii >= 0; --ii)
                {
                    ll x = rec_sum(i, 0, ii, 0, sums);
                    if(x <= k && x > ans)
                        ans = x;
                }
            }
        }
        for(ll i = 1; i < n; ++i)
            for(ll j = 1; j < m; ++j)
            {
                for(ll l = 1; l <= j + 1; ++l)
                {
                    dp[i][j][l] = rec_sum(i, j, i, j - l + 1, sums) + max(dp[i - 1][j][l], (ll)0);
                    if(dp[i][j][l] <= k)
                        ans = max(ans, dp[i][j][l]);
                    else
                    {
                        for(ll ii = i - 1; ii >= 0; --ii)
                        {
                            ll x = rec_sum(i, j, ii, j - l + 1, sums);
                            if(x <= k && x > ans)
                                ans = x;
                        }
                    }
                }
            }
        return ans;
    }

private:
    ll rec_sum(ll i1, ll j1, ll i2, ll j2, const vector<vector<ll>>& sums)
    {
        return sums[i1 + 1][j1 + 1] - sums[i1 + 1][j2] - sums[i2][j1 + 1] + sums[i2][j2];
    }
};
