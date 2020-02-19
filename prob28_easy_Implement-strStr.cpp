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

using namespace std;

// O(MN) 算法
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

// KMP 算法 https://leetcode-cn.com/problems/implement-strstr/solution/kmp-suan-fa-xiang-jie-by-labuladong/
// 确定有限状态机
// 参考《算法4》
