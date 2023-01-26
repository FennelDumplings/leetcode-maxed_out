// prob140: Word Break II

/*
 * Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.
 * Note:
 * The same word in the dictionary may be reused multiple times in the segmentation.
 * You may assume the dictionary does not contain duplicate words.
 */

/*
 * Example 1:
 * Input:
 * s = "catsanddog"
 * wordDict = ["cat", "cats", "and", "sand", "dog"]
 * Output:
 * [
 *   "cats and dog",
 *   "cat sand dog"
 * ]
 * Example 2:
 * Input:
 * s = "pineapplepenapple"
 * wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
 * Output:
 * [
 *   "pine apple pen apple",
 *   "pineapple pen apple",
 *   "pine applepen apple"
 * ]
 * Explanation: Note that you are allowed to reuse a dictionary word.
 * Example 3:
 * Input:
 * s = "catsandog"
 * wordDict = ["cats", "dog", "sand", "and", "cat"]
 * Output:
 * []
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        vector<int> dp(n, 0);
        vector<vector<string>> items(n, vector<string>());
        dfs(s, words, 0, dp, items);
        return items[0];
    }

private:
    bool dfs(const string& s, const unordered_set<string>& wordDict, int left, vector<int>& dp, vector<vector<string>>& items)
    {
        int n = (int)s.size();
        if(left >= n)
            return true;

        if(dp[left] != 0)
            return dp[left] == 1;

        for(int i = left; i < n; ++i)
        {
            string word = s.substr(left, i - left + 1);
            if(wordDict.find(word) != wordDict.end())
            {
                if(dfs(s, wordDict, i + 1, dp, items))
                {
                    if(i + 1 == n)
                    {
                        items[left].push_back(word);
                    }
                    else
                    {
                        for(const string& item_right: items[i + 1])
                        {
                            items[left].push_back(word + ' ' + item_right);
                        }
                    }
                    dp[left] = 1;
                }
            }
        }
        if(dp[left] != 1) dp[left] = -1;
        return dp[left];
    }
};
