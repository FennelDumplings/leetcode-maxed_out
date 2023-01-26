// prob472: Concatenated Words

/*
 * https://leetcode-cn.com/problems/concatenated-words/
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        if(words.empty()) return {};
        vector<string> result;
        wordDict = unordered_set<string>(words.begin(), words.end());
        for(const string& word: words)
        {
            if(word.empty()) continue;
            // lc140
            if(wordBreak(word))
                result.push_back(word);
        }
        return result;
    }

private:
    unordered_set<string> wordDict;

    // lc140
    bool dfs(const string& s, int left, vector<int>& dp)
    {
        int n = (int)s.size();
        if(left >= n)
        {
            return true;
        }

        if(dp[left] != 0)
            return dp[left] == 1;

        dp[left] = -1;
        for(int i = left; i < n; ++i)
        {
            string word = s.substr(left, i - left + 1);
            if(word == s) continue;
            if(wordDict.find(word) != wordDict.end())
            {
                if(dfs(s, i + 1, dp))
                {
                    dp[left] = 1;
                    return true;
                }
            }
        }
        return false;
    }

    // lc140
    bool wordBreak(string s) {
        int n = s.size();
        vector<int> dp(n, 0);
        dfs(s, 0, dp);
        return dp[0] == 1;
    }
};
