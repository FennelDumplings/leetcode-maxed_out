// prob567: Permutation in String

/*
 * Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words,
 * one of the first string's permutations is the substring of the second string.
 */

/*
 * Example 1:
 * Input: s1 = "ab" s2 = "eidbaooo"
 * Output: True
 * Explanation: s2 contains one permutation of s1 ("ba").
 * Example 2:
 * Input:s1= "ab" s2 = "eidboaoo"
 * Output: False
 */

/*
 * Note:
 * The input strings only contain lower case letters.
 * The length of both given strings is in range [1, 10,000].
 */

#include <string>
#include <vector>

using namespace std;

// 字符计数
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        // s1 是模式串
        if(s2.empty()) return false;
        int n = s2.size(), m = s1.size();
        if(n < m) return false;
        // n >= m
        vector<int> pattern_key = _build_key(s1, 0, m - 1); // 传入闭区间
        vector<int> key = _build_key(s2, 0, m - 1); // 传入闭区间
        if(_compare_key(pattern_key, key))
            return true;
        for(int i = 1; i <= n - m; ++i)
        {
            //
            _modify_key(s2, key, i, m);
            if(_compare_key(pattern_key, key))
                return true;
        }
        return false;
    }

private:
    vector<int> _build_key(const string& s, int left, int right)
    {
        // 调用方保证 left 和 right 的合法性
        vector<int> result(26, 0);
        for(int i = left; i <= right; ++i)
            ++result[s[i] - 'a'];
        return result;
    }

    void _modify_key(const string& s, vector<int>& key, int idx, int m)
    {
        int to_be_removed_idx = idx - 1;
        int new_idx = idx + m - 1;
        --key[s[to_be_removed_idx] - 'a'];
        ++key[s[new_idx] - 'a'];
    }

    bool _compare_key(const vector<int>& key1, const vector<int>& key2)
    {
        int n = key1.size(), m = key2.size();
        if(n != m) return false;
        for(int i = 0; i < n; ++i)
        {
            if(key1[i] != key2[i])
                return false;
        }
        return true;
    }
};

// 字符串哈希, 相比438不适用的情况，本题性能与字符计数相当
// 因为只做判断不要求所有结果，冲突一次就退出了
class Solution_2 {
public:
    bool checkInclusion(string s1, string s2) {
        // s1 是模式串
        if(s2.empty()) return false;
        int n = s2.size(), m = s1.size();
        if(n < m) return false;
        // n >= m
        vector<int> pattern_key = _build_key(s1, 0, m - 1); // 传入闭区间
        int pattern_hashcode = _build_hashcode(s1, 0, m - 1); // 传入闭区间
        int hashcode = _build_hashcode(s2, 0, m - 1); // 传入闭区间
        if(pattern_hashcode == hashcode && _compare(pattern_key, s2, 0, m - 1)) // 传入闭区间
            return true;
        for(int i = 1; i <= n - m; ++i)
        {
            _modify_hashcode(s2, hashcode, i, m);
            if(pattern_hashcode == hashcode && _compare(pattern_key, s2, i, m - 1 + i)) // 传入闭区间
                return true;
        }
        return false;
    }

private:
    int _build_hashcode(const string& s, int left, int right)
    {
        // 调用方保证 left 和 right 的合法性
        int result = 0;
        for(int i = left; i <= right; ++i)
            result += s[i] - 'a';
        return result;
    }

    void _modify_hashcode(const string& s, int& hashcode, int idx, int m)
    {
        int to_be_removed_idx = idx - 1;
        int new_idx = idx + m - 1;
        hashcode -= s[to_be_removed_idx];
        hashcode += s[new_idx];
    }

    bool _compare(const vector<int>& pattern_key, const string& s, int left, int right)
    {
        // pattern_key -- 模式串的字符计数，s -- 滑窗所在串，[left, right] -- 滑窗在s中的区间
        vector<int> key = _build_key(s, left, right);
        return _compare_key(pattern_key, key);
    }

    bool _compare_key(const vector<int>& key1, const vector<int>& key2)
    {
        int n = key1.size(), m = key2.size();
        if(n != m) return false;
        for(int i = 0; i < n; ++i)
        {
            if(key1[i] != key2[i])
                return false;
        }
        return true;
    }

    vector<int> _build_key(const string& s, int left, int right)
    {
        // 调用方保证 left 和 right 的合法性
        vector<int> result(26, 0);
        for(int i = left; i <= right; ++i)
            ++result[s[i] - 'a'];
        return result;
    }
};
