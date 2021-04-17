// prob1416: Restore The Array

/*
 * https://leetcode-cn.com/problems/restore-the-array/
 */

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int numberOfArrays(string s, int k) {
        L = get_len(k);
        L_pow = pow(10, L - 1);
        int n = s.size();

        // check[i] := s.substr(i, L) 是否小于等于 k，不关心前导零
        if(n - L + 1 > 0)
        {
            check = vector<bool>(n - L + 1, false);
            ll num = 0;
            for(int i = 0; i < L; ++i)
            {
                num *= 10;
                num += s[i] - '0';
            }
            if(num <= k) check[0] = true;
            for(int i = 1; i < n - L + 1; ++i)
            {
                num %= L_pow;
                num *= 10;
                num += s[i + L - 1] - '0';
                if(num <= k)
                    check[i] = true;
            }
        }

        // dp[i] := [i..n-1] 的方案数
        dp = vector<int>(n + 1, -1);
        dp[n] = 1;
        int ans = solve(s, 0);
        return ans;
    }

private:
    int L_pow; // 10 ^ L
    int L;
    vector<bool> check;
    vector<int> dp;
    const int MOD = 1e9 + 7;
    using ll = long long;

    int solve(const string& s, int i)
    {
        if(dp[i] != -1)
            return dp[i];
        if(s[i] == '0')
            return dp[i] = 0;
        int n = s.size();
        dp[i] = 0;
        for(int j = i + 1; j <= min(n, L + i); ++j)
        {
            if(j - i < L || check[i])
                dp[i] = ((ll)dp[i] + solve(s, j)) % MOD;
        }
        return dp[i];
    }

    int get_len(int K)
    {
        int ans = 0;
        while(K)
        {
            ++ans;
            K /= 10;
        }
        return ans;
    }
};
