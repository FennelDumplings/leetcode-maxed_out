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
#include <unordered_map>

using namespace std;

// O(MN) 算法
// 基本的双指针
class Solution_9 {
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
    // MP 模板 可套用
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

// MP 算法
class Solution_4 {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        vector<int> mpnext = get_mp_next(needle);
        return mp_match(haystack, needle, mpnext);
    }

private:
    int mp_match(const string& s, const string& p, const vector<int>& mpnext)
    {
        int n = s.size(), m = p.size();
        for(int i = 0, j = 0; i < n; ++i)
        {
            while(j > -1 && s[i] != p[j])
                j = mpnext[j];
            ++j;
            if(j == m)
                return i - m + 1;
        }
        return -1;
    }

    vector<int> get_mp_next(const string& p)
    {
        int m = p.size();
        vector<int> mpnext(m + 1, -1);
        for(int i = 0, j = -1; i < m; ++i)
        {
            while(j > -1 && p[i] != p[j])
                j = mpnext[j];
            // j == -1 或 p[i] == p[j]
            ++j;
            mpnext[i + 1] = j;
        }
        return mpnext;
    }
};

// KMP
class Solution_5 {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        vector<int> kmpnext = get_kmp_next(needle);
        return kmp_match(haystack, needle, kmpnext);
    }

private:
    int kmp_match(const string& s, const string& p, const vector<int>& kmpnext)
    {
        int n = s.size(), m = p.size();
        for(int i = 0, j = 0; i < n; ++i)
        {
            while(j > -1 && s[i] != p[j])
                j = kmpnext[j];
            ++j;
            if(j == m)
                return i - m + 1;
        }
        return -1;
    }

    vector<int> get_kmp_next(const string& p)
    {
        int m = p.size();
        vector<int> kmpnext(m + 1, -1);
        for(int i = 0, j = -1; i < m; ++i)
        {
            while(j > -1 && p[i] != p[j])
                j = kmpnext[j];
            // j == -1 或 p[i] == p[j]
            ++j;
            if(p[i + 1] == p[j])
                kmpnext[i + 1] = kmpnext[j];
            else
                kmpnext[i + 1] = j;
        }
        return kmpnext;
    }
};

// BM
class Solution_6 {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        unordered_map<char, int> bmbc;
        get_bmbc(haystack, needle, bmbc);
        vector<int> bmgs = get_bmgs(needle);
        return bm_match(haystack, needle, bmbc, bmgs);
    }

    int bm_match(const string& s, const string& p, unordered_map<char, int>& bmbc, const vector<int>& bmgs)
    {
        int n = s.size(), m = p.size();
        int i = 0;
        while (i <= n - m)
        {
            int j = m - 1;
            while(j >= 0 && p[j] == s[i + j])
                --j;
            if(j < 0)
            {
                return i;
                // i += bmgs[0]; // 找到完整匹配后仍继续往后找下一个完整匹配
            }
            else
               i += max(bmgs[j], bmbc[s[i + j]] - m + 1 + j);
        }
        return -1;
    }

    void get_bmbc(const string& s, const string& p, unordered_map<char, int>& bmbc)
    {
        int m = p.size();
        for(const char& ch: s)
            if(bmbc.find(ch) == bmbc.end())
                bmbc[ch] = m;
        for(int j = 1; j < m; ++j)
        {
            if(bmbc[p[m - 1 - j]] != m)
                continue;
            bmbc[p[m - 1 - j]] = j;
        }
    }

    vector<int> get_bmgs(const string& p)
    {
        // 若一个字符同时符合上述两种情况，那么我们选取最小的bmGs[j]。
        // 比如当模式传中既有子串可以匹配上好后串，又有前缀可以匹配好后串的后串，
        // 那么此时我们应该按照前者来移动模式串，也就是bmGs[j]较小的那种情况。
        // 故而每次修改bmGs[j]都应该使其变小
        // 因此代码中 1,2,3 的顺序是必要的
        int m = p.size();
        vector<int> bmgs(m, 0);
        vector<int> suffix(m, 0);
        get_suff(p, suffix); // suffix[j] := 以 j 为结尾的子串匹配好后缀的最长匹配长度
        // 1. 没有好后缀 没有公共前缀
        for(int j = 0; j < m; ++j)
            bmgs[j] = m;
        // 2. 没有好后缀 有公共前缀 调用 suffix 但是要右移一位 类似KMP里的next数组
        int j = 0;
        for(int i = m - 1; i >= 0; --i)
            if(suffix[i] == i + 1)
                for(; j < m - 1 - i; ++j)
                    if(bmgs[j] == m) //保证每个位置不会重复修改
                        bmgs[j] = m - 1 - i;
        // 3. 有好后缀 有公共前缀
        for(int i = 0; i < m - 1; ++i)
            bmgs[m - 1 - suffix[i]] = m - 1 - i; //移动距离
        return bmgs;
    }

    void get_suff(const string& p, vector<int>& suffix)
    {
        // 为了实现好后缀规则，需要定义一个数组suffix，其中suffix[j] = s 表示以 j 为右边界，
        // 与模式串后缀匹配的最大长度，
        // 即满足p[j-s..j] == P[m-1-s..m-1] 的最大长度 s。
        int m = p.size();
        suffix[m - 1] = m;
        int k;
        for(int j = m - 2; j >= 0; --j)
        {
            k = j;
            // k = j - s;
            while(k >= 0 && p[k] == p[m - 1 - j + k])
                --k;
            suffix[j] = j - k;
        }
    }
};

// Sunday
class Solution_7 {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        unordered_map<char, int> shift;
        get_shift(haystack, needle, shift);
        return sunday_match(haystack, needle, shift);
    }

    int sunday_match(const string& s, const string& p, unordered_map<char, int>& shift)
    {
        int n = s.size(), m = p.size();
        int i = 0;
        while (i <= n - m)
        {
            int j = m - 1;
            while(j >= 0 && p[j] == s[i + j])
                --j;
            if(j < 0)
                return i;
            else
            {
                if(i + m >= n)
                    return -1;
                i += shift[s[i + m]];
            }
        }
        return -1;
    }

    void get_shift(const string& s, const string& p, unordered_map<char, int>& shift)
    {
        int m = p.size();
        for(const char& ch: s)
            if(shift.find(ch) == shift.end())
                shift[ch] = m + 1;
        for(const char& ch: p)
            if(shift.find(ch) == shift.end())
                shift[ch] = m + 1;
        for(int j = 0; j < m; ++j)
        {
            if(shift[p[m - 1 - j]] != m + 1)
                continue;
            shift[p[m - 1 - j]] = j + 1;
        }
    }
};

// horspool
class Solution_8 {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        int m = needle.size();
        vector<int> shift(26, m);
        get_shift(needle, shift);
        vector<int> matches = horspool_match(haystack, needle, shift);
        if(matches.empty())
            return -1;
        return matches.front();
    }

private:
    vector<int> horspool_match(const string& s, const string& p, const vector<int>& shift)
    {
        int m = p.size(), n = s.size();
        int i = 0;
        vector<int> result;
        while(i <= n - m)
        {
            // s[i..i+m-1] 与 p[0..m-1]
            bool match = false;
            for(int j = m - 1; j >= 0; --j)
            {
                if(s[i + j] != p[j])
                    break;
                if(j == 0)
                    match = true;
            }
            if(match)
                result.push_back(i);
            i += shift[s[i + m - 1] - 'a'];
        }
        return result;
    }

    void get_shift(const string& p, vector<int>& shift)
    {
        int m = p.size();
        for(int i = 0; i < m - 1; ++i)
            shift[p[i] - 'a'] = min(shift[p[i] - 'a'], m - i - 1);
    }
};

// 后缀数组 + 二分
class Solution {
public:
    int strStr(string s, string p) {
        if(p.empty()) return 0;
        if(s.empty()) return -1;
        vector<int> sa = get_sa(s);
        vector<int> matches = match(s, sa, p);
        if(matches.empty()) return -1;
        return *min_element(matches.begin(), matches.end());
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

    vector<int> match(string_view s, vector<int>& sa, string_view p)
    {
        int n = s.size(), m = p.size();
        int left = 0, right = n - 1;
        while(left < right)
        {
            int mid = (left + right) / 2;
            // 比较 s 从 sa[mid] 开始长度为 m 的子串与 p
            if(s.substr(sa[mid], min(m, n - sa[mid])) < p)
                left = mid + 1;
            else
                right = mid;
        }
        vector<int> result;
        while(left < n && s.substr(sa[left], min(m, n - sa[left])) == p)
        {
            result.push_back(sa[left]);
            ++left;
        }
        return result;
    }
};
