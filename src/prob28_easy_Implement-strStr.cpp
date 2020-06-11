// prob28: Implement strStr

/*
 * Implement strStr().
 *
 * Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
 */

/*
 * Example 1:
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 * Example 2:
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 */

/*
 * Clarification:
 * What should we return when needle is an empty string? This is a great question to ask during an interview.
 * For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().
 */

#include <string>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

// O(MN) 算法
// 基本的双指针
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        if(haystack.empty()) return -1;
        int n = haystack.size(), m = needle.size();
        if(n < m) return -1;
        int left = 0;
        while(left <= n - m)
        {
            if(haystack[left] == needle[0])
            {
                int right = left + 1;
                while(right - left < m)
                {
                    if(haystack[right] == needle[right - left]) ++right;
                    else break;
                }
                if(right - left == m) return left;
            }
            ++left;
        }
        return -1;
    }
};

// 字符串哈希(RK算法)
// 哈希值是字符的简单相加
// 如果哈希值不同则不匹配，哈希值相同，则需要在逐字比对，因为可能碰撞
class Solution_2 {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        if(haystack.empty()) return -1;
        int n = haystack.size(), m = needle.size();
        if(n < m) return -1;

        // n > 0, m > 0, n >= m
        int hash_pattern = hash(needle);
        string start_substr = haystack.substr(0, m);
        int hash_substr = hash(start_substr);
        if(hash_substr == hash_pattern)
        {
            int i = 0;
            while(i < m && haystack[i] == needle[i])
                ++i;
            if(i == m) return 0;
        }

        for(int i = 1; i <= n - m; ++i)
        {
            hash_substr = hash_substr - haystack[i - 1] + haystack[i + m - 1];
            if(hash_substr == hash_pattern)
            {
                int j = 0;
                while(j < m && haystack[i + j] == needle[j])
                    ++j;
                if(j == m) return i;
            }
        }
        return -1;
    }

private:
    int hash(const string& s)
    {
        int m = s.size();
        int result = 0;
        for(int i = 0; i < m; ++i)
            result += (s[i] - 'a');
        return result;
    }
};

// 字符串哈希
// 提前把主串上所有前缀的哈希都算出来
// p, mod 的质数选取
//     201326611
//     402653189
//     1610612741
// hash[i] = (hash[i-1]*p + idx(A[i - 1])) % MOD; idx(x) = x + 1; i 从 1 开始
//    hash[i] i = 1..n 求出之后，子串 [l..r] 的哈希值可以O(1)获取, 类似与前缀和的思路
//    hash = ((hash[r] - hash[l - 1] * p ^ (r - l + 1)) % mod + mod) % mod
// 如果哈希值不同则不匹配，哈希值相同，则需要在逐字比对，因为可能碰撞, 但碰撞概率极低
class Solution_3_1 {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        if(haystack.empty()) return -1;
        int n = haystack.size(), m = needle.size();
        if(n < m) return -1;

        // n > 0, m > 0, n >= m
        // 主串的前缀哈希数组
        const int p = 201326611;
        vector<unsigned long long> prefix_hash(n + 1, 0);
        vector<unsigned long long> pp(n + 1, 0); //使用ull产生溢出相当于对2^64 取模，避免了低效的取模运算
        pp[0] = 1;
        for(int i = 1; i <= n; ++i)
        {
            prefix_hash[i] = prefix_hash[i - 1] * p + _idx(haystack[i - 1]);
            pp[i] = pp[i - 1] * p;
        }
        // 模式串的哈希值
        unsigned long long pattern_hash = 0;
        for(int i = 0; i < m; ++i)
            pattern_hash = (pattern_hash * p + _idx(needle[i]));

        // 长度为 m 的子串, hash数组中对应位置 [l, r] -- [1..n-m+1, m..n]
        // p 的幂，只需要 m - 1 次
        for(int i = 1; i <= n - m + 1; ++i)
        {
            int l = i, r = i + m - 1;
            unsigned long long hash = (prefix_hash[r] - prefix_hash[l - 1] * pp[m]);
            if(hash == pattern_hash)
                return i - 1;
        }
        return -1;
    }

private:
    int _idx(char x)
    {
        return x - 'a' + 1;
    }
};
class Solution_3_2 {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        if(haystack.empty()) return -1;
        int n = haystack.size(), m = needle.size();
        if(n < m) return -1;

        // n > 0, m > 0, n >= m
        const int MOD = 1610612741;
        const int p = 201326611;
        // 主串的前缀哈希数组
        vector<long long> prefix_hash(n + 1, 0);
        vector<long long> pp(n + 1, 0); // 使用 MOD 的时候不能用 unsigned long long
        pp[0] = 1;
        for(int i = 1; i <= n; ++i)
        {
            prefix_hash[i] = (prefix_hash[i - 1] * p + _idx(haystack[i - 1])) % MOD;
            pp[i] = (pp[i - 1] * p) % MOD;
        }
        // 模式串的哈希值
        long long pattern_hash = 0;
        for(int i = 0; i < m; ++i)
            pattern_hash = (pattern_hash * p + _idx(needle[i])) % MOD;

        // 长度为 m 的子串, hash数组中对应位置 [l, r] -- [1..n-m+1, m..n]
        // p 的幂，只需要 m - 1 次
        for(int i = 1; i <= n - m + 1; ++i)
        {
            int l = i, r = i + m - 1;
            long long hash = ((prefix_hash[r] - prefix_hash[l - 1] * pp[m]) % MOD + MOD) % MOD;
            if(hash == pattern_hash)
                return i - 1;
        }
        return -1;
    }

private:
    int _idx(char x)
    {
        return x - 'a' + 1;
    }
};

// KMP 算法 https://leetcode-cn.com/problems/implement-strstr/solution/kmp-suan-fa-xiang-jie-by-labuladong/
// 确定有限状态机
// 参考《算法4》
class Solution_3 {
public:
    // KMP 模板 可套用
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        int m = needle.size();
        vector<int> nxt(m + 1);
        return kmp(haystack, needle, nxt);
    }

    void getnext(const string p, vector<int>& nxt) {
        int m = p.size();
        for(int i = 1, j = 0; i < m; ++i)
        {
            while(j > 0 && p[i] != p[j])
                j = nxt[j];
            if(p[i] == p[j])
                ++j;
            nxt[i + 1] = j;
        }
    }

    int match(const string& s, const string& p, const vector<int>& nxt)
    {
        int n = s.size(), m = p.size();
        for(int i = 0, j = 0; i < n; ++i)
        {
            while(j > 0 && s[i] != p[j])
                j = nxt[j];
            if(s[i] == p[j])
                ++j;
            if(j == m)
                return i - m + 1;
        }
        return -1;
    }

    int kmp(const string& s, const string& p, vector<int>& nxt) {
        getnext(p, nxt);
        return match(s, p, nxt);
    }
};
