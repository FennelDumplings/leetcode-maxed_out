// prob1255: Maximum Score Words Formed by Letters

/*
 * https://leetcode-cn.com/problems/maximum-score-words-formed-by-letters/
 */

#include <vector>
#include <string>

using namespace std;

// 枚举 words 的子集，然后 check
class Solution_2 {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int n = words.size();
        vector<int> word_score(n);
        word_cnts.assign(n, vector<int>(26, 0));
        for(int i = 0; i < n; ++i)
        {
            int s = 0;
            for(char ch: words[i])
            {
                ++word_cnts[i][ch - 'a'];
                s += score[ch - 'a'];
            }
            word_score[i] = s;
        }
        cnts.assign(26, 0);
        for(char ch: letters)
            ++cnts[ch - 'a'];
        int ans = 0;
        // 迭代子集枚举
        for(int choose = 1; choose < (1 << n); ++choose)
        {
            vector<int> choose_cnt(26);
            bool flag = true;
            int cand = 0;
            for(int i = 0; i < n; ++i)
            {
                if(choose >> i & 1)
                {
                    cand += word_score[i];
                    for(int j = 0; j < 26; ++j)
                    {
                        choose_cnt[j] += word_cnts[i][j];
                        if(choose_cnt[j] > cnts[j])
                        {
                            flag = false;
                            break;
                        }
                    }
                }
                if(!flag)
                    break;
            }
            if(flag)
                ans = max(ans, cand);
        }
        return ans;
    }

private:
    vector<int> cnts;
    vector<vector<int>> word_cnts;
};

// DFS + 剪枝
class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int n = words.size();
        word_score.assign(n, 0);
        word_cnts.assign(n, vector<int>(26, 0));
        for(int i = 0; i < n; ++i)
        {
            int s = 0;
            for(char ch: words[i])
            {
                ++word_cnts[i][ch - 'a'];
                s += score[ch - 'a'];
            }
            word_score[i] = s;
        }
        cnts.assign(26, 0);
        for(char ch: letters)
            ++cnts[ch - 'a'];
        int ans = 0;
        vector<int> remain_cnt = cnts;
        dfs(0, ans, 0, remain_cnt, n);
        return ans;
    }

private:
    vector<int> word_score;
    vector<int> cnts;
    vector<vector<int>> word_cnts;

    // 递归子集枚举
    void dfs(int pos, int& ans, int s, vector<int>& remain_cnt, const int n)
    {
        if(pos == n)
        {
            ans = max(ans, s);
            return;
        }
        // 不选 words[pos]
        dfs(pos + 1, ans, s, remain_cnt, n);
        // 选 words[pos]
        if(check(remain_cnt, pos))
        {
            for(int i = 0; i < 26; ++i)
                remain_cnt[i] -= word_cnts[pos][i];
            dfs(pos + 1, ans, s + word_score[pos], remain_cnt, n);
            for(int i = 0; i < 26; ++i)
                remain_cnt[i] += word_cnts[pos][i];
        }
    }

    bool check(const vector<int>& remain_cnt, int pos)
    {
        for(int i = 0; i < 26; ++i)
            if(remain_cnt[i] < word_cnts[pos][i])
                return false;
        return true;
    }
};
