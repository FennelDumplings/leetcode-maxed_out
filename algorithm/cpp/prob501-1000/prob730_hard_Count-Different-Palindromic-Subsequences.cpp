// prob: Count Different Palindromic Subsequences

/*
 * Given a string S, find the number of different non-empty palindromic subsequences in S,
 * and return that number modulo 10^9 + 7.
 * Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.
 */

/*
 * Example 1:
 * Input:
 * S = 'bccb'
 * Output: 6Example 2:
 * Input:
 * S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
 * Output: 104860361
 */

/*
 * Note:
 * The length of S will be in the range [1, 1000].
 * Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int countPalindromicSubsequences(string S) {
        if(S.empty()) return 0;
        int n = S.size();
        if(n == 1) return 1;

        vector<vector<int> > dp(n, vector<int>(n, 0));
        for(int i = 0; i < n ; ++i)
            dp[i][i] = 1;

        for(int j = 1; j < n; ++j)
            for(int i = j - 1; i >= 0; --i)
            {
                if(S[i] != S[j])
                    dp[i][j] = dp[i][j - 1] - dp[i + 1][j - 1] + dp[i + 1][j];
                else
                {
                    int l = i + 1, r = j - 1;
                    while(l <= r && S[i] != S[l]) ++l;
                    while(l <= r && S[i] != S[r]) --r;
                    if(l > r)
                        dp[i][j] = 2 * dp[i + 1][j - 1] + 2;
                    else if(l == r)
                        dp[i][j] = 2 * dp[i + 1][j - 1] + 1;
                    else
                        dp[i][j] = 2 * dp[i + 1][j - 1] - dp[l + 1][r - 1];
                }
                dp[i][j] = (dp[i][j] + kMod) % kMod;
            }
        return dp[0][n - 1];
    }

private:
    static constexpr long kMod = 1000000007;
};

// 记忆化递归
// 记忆化递归保存结果用 substr 有拷贝的过程, 时间空间都 O(N)
// 报 MLE
class Solution_2 {
public:
    int countPalindromicSubsequences(string S) {
        return _count(S);
    }

private:
    int _count(const string &s) {
        if(s.empty()) return 0;
        int n = s.size();
        if(n == 1) return 1;

        auto it = mapping.find(s);
        if(it != mapping.end())
            return it -> second;

        long ans = 0;
        if(s[0] == s[n - 1])
        {
            int l = 1, r = n - 2;
            while(l <= r && s[l] != s[0]) ++l;
            while(l <= r && s[r] != s[0]) --r;
            if(l > r)
                ans = _count(s.substr(1, n - 2)) * 2 + 2;
            else if(l == r)
                ans = _count(s.substr(1, n - 2)) * 2 + 1;
            else
                ans = _count(s.substr(1, n - 2)) * 2
                    - _count(s.substr(l + 1, r - l - 1)); // 这里可能出现负数，输出结果的时候保险加上 kMod
        }
        else
        {
            ans = _count(s.substr(0, n - 1))
                + _count(s.substr(1, n - 1))
                - _count(s.substr(1, n - 2));
        }

        return mapping[s] = (ans + kMod) % kMod;
    }

    static constexpr long kMod = 1000000007;
    unordered_map<string, int> mapping; // 保存子问题的结果
};


// 记忆化递归 优化
// 记忆化递归只存区间(start, end)
// 但区间没法哈希，因为长度范围较小(1000) 可以用 start * length + end 把区间哈希到一个整数;
// 可以用 vector 代替哈希表
class Solutina_2_optim {
public:
    int countPalindromicSubsequences(string S) {
        if(S.empty()) return 0;
        int n = S.size();
        if(n == 1) return 1;
        return _count(S, 0, n - 1);
    }

private:
    int _count(const string &s, int start, int end) {
        if(start > end)  return 0;
        if(start == end) return 1;
        int n = s.size();
        int hash_key = start * n + end;
        auto it = mapping.find(hash_key);
        if(it != mapping.end())
            return it -> second;

        long ans = 0;
        if(s[start] == s[end])
        {
            int l = start + 1, r = end - 1;
            while(l <= r && s[l] != s[start]) ++l;
            while(l <= r && s[r] != s[start]) --r;
            if(l > r)
                ans = _count(s, start + 1, end - 1) * 2 + 2;
            else if(l == r)
                ans = _count(s, start + 1, end - 1) * 2 + 1;
            else
                ans = _count(s, start + 1, end - 1) * 2
                    - _count(s, l + 1, r - 1); // 这里可能出现负数，输出结果的时候保险加上 kMod
        }
        else
        {
            ans = _count(s, start, end - 1)
                + _count(s, start + 1, end)
                - _count(s, start + 1, end - 1);
        }

        return mapping[hash_key] = (ans + kMod) % kMod;
    }

    static constexpr long kMod = 1000000007;
    unordered_map<int, int> mapping; // 保存子问题的结果
};


// int 类型键范围较小，用 vector 代替哈希表
// 时间 1064ms -> 60ms; 473.8M -> 32.2M
class Solution_2_optim_2 {
public:
    int countPalindromicSubsequences(string S) {
        if(S.empty()) return 0;
        int n = S.size();
        if(n == 1) return 1;
        mapping = vector<int>(n * (n + 1) + 1, 0);
        return _count(S, 0, n - 1);
    }

private:
    int _count(const string &s, int start, int end) {
        if(start > end)  return 0;
        if(start == end) return 1;

        int n = s.size();
        int hash_key = start * n + end;
        if(mapping[hash_key] > 0) return mapping[hash_key];

        long ans = 0;
        if(s[start] == s[end])
        {
            int l = start + 1, r = end - 1;
            while(l <= r && s[l] != s[start]) ++l;
            while(l <= r && s[r] != s[start]) --r;
            if(l > r)
                ans = _count(s, start + 1, end - 1) * 2 + 2;
            else if(l == r)
                ans = _count(s, start + 1, end - 1) * 2 + 1;
            else
                ans = _count(s, start + 1, end - 1) * 2
                    - _count(s, l + 1, r - 1); // 这里可能出现负数，输出结果的时候保险加上 kMod
        }
        else
        {
            ans = _count(s, start, end - 1)
                + _count(s, start + 1, end)
                - _count(s, start + 1, end - 1);
        }

        return mapping[hash_key] = (ans + kMod) % kMod;
    }

    static constexpr long kMod = 1000000007;
    vector<int> mapping; // 保存子问题的结果
};
