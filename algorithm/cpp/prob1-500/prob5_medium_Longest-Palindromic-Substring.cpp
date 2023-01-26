// prob5: Longest Palindromic Substring

/*
 * Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
 */

/*
 * Example 1:
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 * Example 2:
 * Input: "cbbd"
 * Output: "bb"
 */

#include <string>
#include <vector>

using namespace std;

// 暴力枚举回文串中心
class Solution_3 {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return "";
        int n = s.size();
        if(n == 1) return s;

        int max_len = 1;
        int start = 0;
        for(int i = 0; i < n; ++i)
        {
            // while 循环提前终止，相当于剪枝了一些状态
            int len1 = 1; // s[i] 为中心点的最长回文子串长
            int l = i - 1, r = i + 1;
            while(l >= 0 && r <= n - 1 && s[l] == s[r])
            {
                len1 += 2;
                ++r;
                --l;
            }
            if(len1 > max_len)
            {
                max_len = len1;
                start = l + 1;
            }
            int len2 = 0; // s[i], s[i - 1] 为中心点的最长回文子串长
            l = i - 1;
            r = i;
            while(l >= 0 && r <= n - 1 && s[l] == s[r])
            {
                len2 += 2;
                ++r;
                --l;
            }
            if(len2 > max_len)
            {
                max_len = len2;
                start = l + 1;
            }
        }
        return s.substr(start, max_len);
    }
};

// DP: 朴素DP, 显式的开空间
// dp[i][j] := dp[i][j] 是否是回文子串
// dp[i][j] = 0   (s[i] != s[j])
//          = dp[i + 1][j - 1]   (s[i] == s[j])
// dp[i][i] = 1
// 时空效率都远低于暴力枚举
class Solution_2 {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return "";
        int n = s.size();
        if(n == 1) return s;

        int max_length = 1;
        int max_i = 0;
        vector<vector<bool> > dp(n, vector<bool>(n, 0));
        for(int i = 0; i < n; ++i)
        {
            dp[i][i] = true;
            if(i < n - 1)
                dp[i + 1][i] = true; // 处理 bb 这种情况的转移
        }

        for(int j = 1; j < n; ++j)
            for(int i = j - 1; i >= 0 ; --i)
            {
                // 没有隐含剪枝，速度没有暴力枚举快
                int len = j - i + 1;
                if(s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1];
                if(dp[i][j] && len > max_length)
                {
                    max_i = i;
                    max_length = len;
                }
            }
        return s.substr(max_i, max_length);
    }
};


#include <algorithm>
#include <cmath>

class RMQ
{
public:
    RMQ(){}

    void init(const vector<int>& arr)
    {
        int n = arr.size();
        // 2 ^ m <= n
        // log2(2^m) <= log2(n)
        // m <= log2(n)
        int m = log2(n);
        dp.assign(n + 1, vector<int>(m + 1, 0));
        for(int i = 0; i < n; ++i)
            dp[i][0] = arr[i]; //初始化
        for(int j = 1; (1 << j) <= n; ++j)
            for(int i = 0; i + (1 << j) - 1 < n; ++i)
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r)
    {
        int k = log2(r - l + 1);
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
private:
    vector<vector<int>> dp;
};


class Solution {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return "";
        int n = s.size();
        if(n == 1) return s;

        string t = s;
        reverse(s.begin(), s.end());
        t += '#' + s;
        vector<int> sa = get_sa(t);
        vector<int> rank;
        vector<int> lcp = get_lcp(t, sa, rank);

        RMQ rmq;
        rmq.init(lcp);

        int idx = -1;
        int max_len = 0;
        for(int i = 0; i < n; ++i)
        {
            int j = n * 2 - i;
            int l = rmq.query(min(rank[i], rank[j]), max(rank[i], rank[j]) - 1);
            if(l * 2 + 1 > max_len)
            {
                max_len = l * 2 - 1;
                idx = i - l + 1;
            }
        }
        for(int i = 1; i < n; ++i)
        {
            int j = n * 2 - i + 1;
            int l = rmq.query(min(rank[i], rank[j]), max(rank[i], rank[j]) - 1);
            if(l * 2 > max_len)
            {
                max_len = l * 2;
                idx = i - l ;
            }
        }
        return t.substr(idx, max_len);
    }

private:
    const int ALPHABET = 128;

    vector<int> get_sa(const string& s)
    {
        vector<int> c(ALPHABET);
        int n = s.size();
        vector<int> rank(n); // 第一关键字
        vector<int> y(n); // 第二关键字
        vector<int> sa(n);

        for(int i = 0; i < n; ++i)
        {
            ++c[s[i]];
            rank[i] = s[i];
        }
        for(int i = 1; i < ALPHABET; ++i)
            c[i] += c[i - 1];
        for(int i = n - 1; i >= 0; --i)
        {
            sa[--c[rank[i]]] = i;
        }

        int m = ALPHABET; // 关键字种类数
        for(int k = 1; k <= n; k <<= 1)
        {
            int p = 0;
            for(int i = n - k; i < n; ++i)
                y[p++] = i;
            for(int i = 0; i < n; ++i)
                if(sa[i] >= k)
                    y[p++] = sa[i] - k;

            c.assign(m, 0);
            for(int i = 0; i < n; ++i)
                ++c[rank[i]];
            for(int i = 1; i < m; ++i)
                c[i] += c[i - 1];
            for(int i = n - 1; i >= 0; --i)
                sa[--c[rank[y[i]]]] = y[i];

            rank.swap(y);
            p = 1; // 分配的关键字
            rank[sa[0]] = 0;
            for(int i = 1; i < n; ++i)
            {
                // 此时 y 持有的是长为 len 的第一关键字
                // 长为 len 的第二关键字从 sa 获得
                // 合并后的长为 len * 2 的第一关键字放在 rank
                if(y[sa[i - 1]] == y[sa[i]] &&
                        (sa[i - 1] + k >= n ? -1 : y[sa[i - 1] + k]) == (sa[i] + k >= n ? -1 : y[sa[i] + k]))
                    rank[sa[i]] = p - 1;
                else
                {
                    rank[sa[i]] = p;
                    p++;
                }
            }

            // 下一轮的关键字种类数
            if(p >= n)
                break;
            m = p;
        }

        return sa;
    }

    vector<int> get_lcp(const string& s, const vector<int>& sa, vector<int>& rank)
    {
        int n = s.size();
        rank.assign(n, 0);
        for(int i = 0; i < n; ++i)
            rank[sa[i]] = i;

        int h = 0;
        vector<int> lcp(n);
        lcp[n - 1] = 0;
        for(int i = 0; i < n; ++i)
        {
            if(rank[i] == 0)
                continue;
            int j = sa[rank[i] - 1];

            // h 先减去首字母的 1 长度
            if(h > 0)
                --h;
            while(j + h < n && i + h < n && s[j + h] == s[i + h])
                ++h;

            lcp[rank[i] - 1] = h;
        }
        return lcp;
    }
};
