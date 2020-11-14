// prob30: Substring with Concatenation of All Words

/*
 * You are given a string, s, and a list of words, words, that are all of the same length.
 * Find all starting indices of substring(s) in s that is a concatenation of each word
 * in words exactly once and without any intervening characters.
 */

/*
 * Example 1:
 *
 * Input:
 *   s = "barfoothefoobarman",
 *   words = ["foo","bar"]
 * Output: [0,9]
 * Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
 * The output order does not matter, returning [9,0] is fine too.
 * Example 2:
 *
 * Input:
 *   s = "wordgoodgoodgoodbestword",
 *   words = ["word","good","best","word"]
 * Output: []
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return vector<int>();
        int n = s.size();

        int words_num = words.size();
        int pattern_len = words[0].size();
        if(pattern_len == 0)
        {
            vector<int> result(n, 0);
            for(int i = 0; i < n; ++i)
                result[i] = i;
            return result;
        }
        int total_match_len = pattern_len * words_num;
        if(n < total_match_len) return vector<int>();

        // pattern_len > 0, words_num > 0, n >= total_match_len
        unordered_map<string, int> mapping;
        for(int i = 0; i < words_num; ++i)
        {
            if(mapping.find(words[i]) == mapping.end())
                mapping[words[i]] = 1;
            else
                mapping[words[i]]++;
        }
        vector<string> matched = vector<string>(words_num, string(pattern_len, ' '));
        vector<int> result;
        for(int i = 0; i <= n - total_match_len; ++i)
        {
            bool match = true;
            int matched_num = 0;
            for(int j = 0; j < words_num; ++j)
            {
                if(!check(s, i + j * pattern_len, pattern_len, mapping, matched, matched_num))
                {
                    match = false;
                    break;
                }
            }
            if(match)
                result.push_back(i);
            for(int k = 0; k < matched_num; ++k)
                mapping[matched[k]]++;
        }
        return result;
    }

private:
    bool check(const string& s, int i, int pattern_len, unordered_map<string, int> &mapping,
            vector<string> &matched, int &matched_num)
    {
        string sub = s.substr(i, pattern_len);
        auto it = mapping.find(sub);
        if(it != mapping.end() && mapping[sub] > 0)
        {
            mapping[sub]--;
            matched[matched_num++] = sub;
            return true;
        }
        else
        {
            return false;
        }
    }
};

// 每次移动i时重新建mapping, 不是很好
// 时间空间都上升明显
class Solution_2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return vector<int>();
        int n = s.size();

        int words_num = words.size();
        int pattern_len = words[0].size();
        if(pattern_len == 0)
        {
            vector<int> result(n, 0);
            for(int i = 0; i < n; ++i)
                result[i] = i;
            return result;
        }
        int total_match_len = pattern_len * words_num;
        if(n < total_match_len) return vector<int>();

        // pattern_len > 0, words_num > 0, n >= total_match_len
        vector<int> result;
        for(int i = 0; i <= n - total_match_len; ++i)
        {
            unordered_map<string, int> mapping;
            for(int i = 0; i < words_num; ++i)
            {
                if(mapping.find(words[i]) == mapping.end())
                    mapping[words[i]] = 1;
                else
                    mapping[words[i]]++;
            }
            bool match = true;
            for(int j = 0; j < words_num; ++j)
            {
                if(!check(s, i + j * pattern_len, pattern_len, mapping))
                {
                    match = false;
                    break;
                }
            }
            if(match)
                result.push_back(i);
        }
        return result;
    }

private:
    bool check(const string& s, int i, int pattern_len, unordered_map<string, int> &mapping)
    {
        string sub = s.substr(i, pattern_len);
        auto it = mapping.find(sub);
        if(it != mapping.end() && mapping[sub] > 0)
        {
            mapping[sub]--;
            return true;
        }
        else
        {
            return false;
        }
    }
};

// 划窗/双指针+精巧的字符串枚举
class Solution_2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return vector<int>();
        int n = s.size();

        int words_num = words.size();
        int pattern_len = words[0].size();
        if(pattern_len == 0)
        {
            vector<int> result(n, 0);
            for(int i = 0; i < n; ++i)
                result[i] = i;
            return result;
        }
        int total_match_len = pattern_len * words_num;
        if(n < total_match_len) return vector<int>();

        // pattern_len > 0, words_num > 0, n >= total_match_len
        unordered_map<string, int> mapping;
        for(int i = 0; i < words_num; ++i)
        {
            if(mapping.find(words[i]) == mapping.end())
                mapping[words[i]] = 1;
            else
                mapping[words[i]]++;
        }
        // 到这里与原始解法都一样

        vector<int> result;
        unordered_map<string, int> matched;
        for(int i = 0; i < words_num; ++i)
            if(matched.find(words[i]) == matched.end())
                matched[words[i]] = 0;
        for(int i = 0; i < pattern_len; ++i)
        {
            // 切分为每段长为 pattern_len 的序列，共有 pattern_len - 1 种
            int matched_num = 0;
            int left = i, right = left + pattern_len - 1;
            for(int i = 0; i < words_num; ++i)
                matched[words[i]] = 0;
            while(right < n && left <= n - total_match_len)
            {
                string cur = s.substr(right - pattern_len + 1, pattern_len);
                if(mapping.find(cur) == mapping.end())
                {
                    // cur 不匹配 word 中的词，则此前匹配到的词全都作废
                    // 复位
                    matched_num = 0;
                    for(int i = 0; i < words_num; ++i)
                        matched[words[i]] = 0;
                    left = right + 1;
                    right += pattern_len;
                }
                else if(mapping[cur] <= matched[cur])
                {
                    // cur 匹配了 words 中的词，但是此前已经匹配到了个数
                    // 右移left 直到第一个 cur
                    while(s.substr(left, pattern_len) != cur)
                    {
                        matched[s.substr(left, pattern_len)]--;
                        --matched_num;
                        left += pattern_len;
                    }
                    left += pattern_len;
                    right += pattern_len;
                }
                else
                {
                    ++matched_num;
                    matched[cur]++;
                    if(matched_num == words_num)
                    {
                        result.push_back(left);
                        // left 往右移动一个词
                        matched[s.substr(left, pattern_len)]--;
                        left += pattern_len;
                        --matched_num;
                    }
                    right += pattern_len;
                }
            }
        }
        return result;
    }
};


// 其他解法：字符串哈希,Trie,AC自动机

