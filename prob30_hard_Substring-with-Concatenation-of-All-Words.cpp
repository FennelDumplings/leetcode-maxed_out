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
