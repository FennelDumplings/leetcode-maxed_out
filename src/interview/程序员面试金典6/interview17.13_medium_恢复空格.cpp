// interview17.13: 恢复空格

/*
 * https://leetcode-cn.com/problems/re-space-lcci/
 */

#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

class Solution {
public:
    int respace(vector<string>& dictionary, string sentence) {
        for(const string& word: dictionary)
        {
            int len = word.size();
            lens.insert(len);
            words.insert(word);
        }
        int n = sentence.size();
        vector<int> dp(n, -1);
        return dfs(0, sentence, dp);
    }

private:
    set<int> lens;
    unordered_set<string> words;

    int dfs(int pos, const string& s, vector<int>& dp)
    {
        int n = dp.size();
        if(pos == n) return 0;
        if(dp[pos] != -1) return dp[pos];

        dp[pos] = n - pos;

        for(int l: lens)
        {
            string cur = s.substr(pos, l);
            if(words.count(cur) == 0)
                continue;
            if(pos + l > n) continue;
            dp[pos] = min(dp[pos], dfs(pos + l, s, dp));
        }
        if(pos < n)
            dp[pos] = min(dp[pos], 1 + dfs(pos + 1, s, dp));
        return dp[pos];
    }
};

//
class Solution_2 {
public:
    int respace(vector<string>& dictionary, string sentence) {
        for(const string& word: dictionary)
        {
            int len = word.size();
            lens.insert(len);
            words.insert(word);
        }
        int n = sentence.size();
        vector<int> dp(n, -1);
        return dfs(0, sentence, dp);
    }

private:
    set<int> lens;
    unordered_set<string> words;

    int dfs(int pos, const string& s, vector<int>& dp)
    {
        int n = dp.size();
        if(pos == n) return 0;
        if(dp[pos] != -1) return dp[pos];

        dp[pos] = n - pos;

        for(int l: lens)
        {
            string cur = s.substr(pos, l);
            if(words.count(cur) == 0)
                continue;
            if(pos + l > n) continue;
            dp[pos] = min(dp[pos], dfs(pos + l, s, dp));
        }
        if(pos < n)
            dp[pos] = min(dp[pos], 1 + dfs(pos + 1, s, dp));
        return dp[pos];
    }
};
