// interview: 最长单词

/*
 * https://leetcode-cn.com/problems/longest-word-lcci/
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

struct Cmp
{
    bool operator()(const string& w1, const string& w2) const
    {
        int l1 = w1.size(), l2 = w2.size();
        if(l1 == l2)
            return w1 < w2;
        return l1 > l2;
    }
};

class Solution {
public:
    string longestWord(vector<string>& words) {
        if(words.empty()) return "";
        for(const string& word: words)
        {
            int len = word.size();
            lens.insert(len);
            words_set.insert(word);
        }
        sort(words.begin(), words.end(), Cmp());
        for(const string& word: words)
        {
            words_set.erase(words_set.find(word));
            if(dfs(word, 0))
                return word;
            words_set.insert(word);
        }
        return "";
    }

private:
    unordered_set<string> words_set;
    set<int> lens;

    bool dfs(const string& word, int pos)
    {
        int n = word.size();
        if(pos == n)
            return true;

        for(int l: lens)
        {
            if(l > n - pos)
                break;
            string cur = word.substr(pos, l);
            if(words_set.count(cur) == 0)
                continue;
            if(dfs(word, pos + l))
                return true;
        }
        return false;
    }
};
