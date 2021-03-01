// prob727: Minimum Window Subsequence

/*
 * https://leetcode-cn.com/problems/minimum-window-subsequence/
 */

#include <string>
#include <vector>

using namespace std;

// 滑动窗口
class Solution {
public:
    string minWindow(string S, string T) {
        if(S == T) return S;
        int n = S.size(), m = T.size();
        int start = 0, end = n - 1;
        // m <= len <= n
        int ls = 0, lt = 0;
        while(ls < n)
        {
            if(S[ls] == T[lt])
            {
                ++lt;
            }
            if(lt == m)
            {
                int right = ls;
                --lt;
                while(lt >= 0)
                {
                    if(S[ls] == T[lt])
                        --lt;
                    --ls;
                }
                ++ls;
                if(right - ls + 1 < end - start + 1)
                {
                    start = ls;
                    end = right;
                }
                lt = 0;
            }
            ++ls;
        }
        if(end - start + 1 == n) return "";
        return S.substr(start, end - start + 1);
    }
};


// dp[i][j] := 两个串分别考虑到 S[0..j], T[0..i]
//             且 S 中以 j 为右端点时，包含 T[0..i] 的最短子串的左端点
//             T[0..i] 与 S[dp[i][j], j] 对应
//             若不存在，为 -1
// 初始化：全初始化 -1
//         dp[0][0] = 0 若 S[0] == T[0]
//         dp[0][j] = j 若 S[j] == T[0]
//                  = dp[0][j - 1]
// 转移：
// dp[i][j] = dp[i - 1][j - 1]   (T[i] == S[j])
//          = dp[i][j - 1]       (T[i] != S[j])

// 双串 dp[i][j]
class Solution_2 {
public:
    string minWindow(string S, string T) {
        if(S == T) return S;
        int n = S.size(), m = T.size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        if(S[0] == T[0])
            dp[0][0] = 0;
        for(int j = 1; j < n; ++j)
        {
            if(S[j] == T[0])
                dp[0][j] = j;
            else
                dp[0][j] = dp[0][j - 1];
        }
        for(int i = 1; i < m; ++i)
            for(int j = 1; j < n; ++j)
            {
                if(S[j] == T[i])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = dp[i][j - 1];
            }

        int left = 0, right = n - 1;
        // 长度 right - left - 1, 若为 n 则为 -1
        for(int j = 0; j < n; ++j)
        {
            if(dp[m - 1][j] == -1)
                continue;
            if(j - dp[m - 1][j] >= right - left)
                continue;
            left = dp[m - 1][j];
            right = j;
        }
        if(right - left + 1 == n)
            return "";
        return S.substr(left, right - left + 1);
    }
};
