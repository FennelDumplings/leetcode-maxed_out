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
// 一个字符串 -> 当成26进制数，算出十进制数，对 long long 范围取模
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

// KMP 算法 https://leetcode-cn.com/problems/implement-strstr/solution/kmp-suan-fa-xiang-jie-by-labuladong/
// 确定有限状态机
// 参考《算法4》
class Solution_3 {
public:
    // KMP 模板 可套用
    int strStr(string haystack, string needle) {
        if(needle.size()==0) return 0;
        vector<int> nxt(needle.size()+5);
        return kmp(haystack, needle, nxt);
    }
    void getnext(string t, vector<int>& nxt) {
        int n = t.size();
        int i=0, k=-1;
        nxt[0] = -1;
        while(i<n) {
            if(k==-1 || t[i]==t[k])
                nxt[++i] = ++k;
            else
                k = nxt[k];
        }
    }
    int kmp(string s, string t, vector<int>& nxt) {
        int slen=s.size(), tlen=t.size();
        int i=0, j=0;
        getnext(t, nxt);
        while(i<slen && j<tlen) {
            if(j==-1 || s[i]==t[j])
                i++, j++;
            else
                j = nxt[j];
        }
        if(j==tlen) return i-j;
        return -1;
    }
};
