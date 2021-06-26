// prob446: Arithmetic Slices II - Subsequence

/*
 * https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/
 */

#include <vector>
#include <unordered_map>

using namespace std;

// TLE
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        if(A.empty()) return 0;
        int n = A.size();
        if(n < 3) return 0;
        using ll = long long;
        unordered_map<int, unordered_map<ll, vector<int>>> mapping; // i -> ([0..i-1] 中的 j:  d -> j 的列表)
        for(int i = 1; i < n; ++i)
        {
            for(int j = 0; j < i; ++j)
                mapping[i][(ll)A[i] - A[j]].push_back(j);
        }
        vector<vector<int>> dp(n, vector<int>(n)); // dp[i][j] := 以 ...j..i 结尾的子序列
        int ans = 0;
        for(int i = 2; i < n; ++i)
            for(int j = 1; j < i; ++j)
            {
                // dp[i][j]
                ll d = (ll)A[i] - A[j];
                for(int k: mapping[j][d])
                {
                    dp[i][j] += 1 + dp[j][k];
                }
                ans += dp[i][j];
            }
        return ans;
    }
};


class Solution_2 {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        if(A.empty()) return 0;
        int n = A.size();
        if(n < 3) return 0;
        using ll = long long;
        vector<unordered_map<ll, int>> dp(n, unordered_map<ll, int>()); // dp[i][d] := 以 i 结尾的公差为 d 子序列
        int ans = 0;
        for(int i = 1; i < n; ++i)
        {
            // dp[i][d]
            for(int j = 0; j < i; ++j)
            {
                ll d = (ll)A[i] - A[j];
                int sum = 0;
                if(dp[j].find(d) != dp[j].end())
                    sum = dp[j][d];
                dp[i][d] += sum + 1;
                ans += sum; // 上面 1 的部分是长度为 2 的，转移时有用但不统计进结果
            }
        }
        return ans;
    }
};

