// prob290: Word Pattern

/*
 * Given a pattern and a string str, find if str follows the same pattern.
 * Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.
 */

/*
 * Example 1:
 * Input: pattern = "abba", str = "dog cat cat dog"
 * Output: true
 * Example 2:
 * Input:pattern = "abba", str = "dog cat cat fish"
 * Output: false
 * Example 3:
 * Input: pattern = "aaaa", str = "dog cat cat dog"
 * Output: false
 * Example 4:
 * Input: pattern = "abba", str = "dog dog dog dog"
 * Output: false
 */

/*
 * Notes:
 * You may assume pattern contains only lowercase letters, and str contains lowercase letters that may be separated by a single space.
 */

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// 从 str 中读取单词 word, 保存在 words 中，用 stringstream 方便
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        if(pattern.empty() || str.empty()) return false;
        int n = str.size();
        vector<string> words;
        int left = 0;
        while(left < n && str[left] == ' ')
            ++left;
        while(left < n)
        {
            int right = left + 1;
            while(right < n && str[right] != ' ')
                ++right;
            words.push_back(str.substr(left, right - left));
            left = right;
            while(left < n && str[left] == ' ')
                ++left;
        }
        if(words.size() != pattern.size()) return false;
        unordered_map<char, string> mapping;
        unordered_map<string, char> mapping_reverse;
        for(int i = 0; i < (int)pattern.size(); ++i)
        {
            auto it = mapping.find(pattern[i]);
            if(it == mapping.end())
                mapping[pattern[i]] = words[i];
            else if(it -> second != words[i])
                return false;

            auto it_reverse = mapping_reverse.find(words[i]);
            if(it_reverse == mapping_reverse.end())
                mapping_reverse[words[i]] = pattern[i];
            else if(it_reverse -> second != pattern[i])
                return false;
        }
        return true;
    }
};
