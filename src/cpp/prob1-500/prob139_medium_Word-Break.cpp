// prob139: Word Break

/*
 * Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
 * Note:
 * The same word in the dictionary may be reused multiple times in the segmentation.
 * You may assume the dictionary does not contain duplicate words.
 */

/*
 * Example 1:
 * Input: s = "leetcode", wordDict = ["leet", "code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet code".
 * Example 2:
 * Input: s = "applepenapple", wordDict = ["apple", "pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
 * Example 3:
 * Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 * Output: false
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        vector<int> dp(n, 0);
        return _solve(s, words, 0, dp);
    }

private:
    bool _solve(const string& s, const unordered_set<string>& wordDict, int left, vector<int>& dp)
    {
        int n = (int)s.size();
        if(left >= n)
            return true;

        if(dp[left] != 0)
            return dp[left] == 1;

        for(int i = left; i < n; ++i)
        {
            if(wordDict.find(s.substr(left, i - left + 1)) != wordDict.end())
            {
                if(_solve(s, wordDict, i + 1, dp))
                {
                    dp[left] = 1;
                    return true;
                }
            }
        }
        dp[left] = -1;
        return false;
    }
};
