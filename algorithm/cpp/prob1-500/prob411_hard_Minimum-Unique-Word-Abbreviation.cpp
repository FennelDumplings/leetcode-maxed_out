// prob411: Minimum Unique Word Abbreviation

/*
 * https://leetcode-cn.com/problems/minimum-unique-word-abbreviation/
 */

#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

using namespace std;

class Solution_2 {
public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        int n = target.size();
        int min_len = n;
        string ans = target;
        dfs(dictionary, target, 0, "", ans, 0, min_len);
        return ans;
    }

private:
    void dfs(const vector<string>& dictionary, const string& word, int left, string abbr, string& ans, int len, int& min_len)
    {
        if(len >= min_len)
            return;
        int n = word.size();
        if(left >= n)
        {
            bool flag = true;
            for(const string &s: dictionary)
                if(check(abbr, s))
                {
                    flag = false;
                    break;
                }
            if(flag)
            {
                min_len = len;
                ans = abbr;
            }
            return;
        }
        for(int i = left; i < n; ++i)
        {
            // [left, i) 是数字，i 是分格字符 [i + 1, n) 是下一个
            string num = "";
            int add_len = 1;
            if(i - left > 0)
            {
                num = to_string(i - left);
                ++add_len;
            }
            dfs(dictionary, word, i + 1, abbr + num + word[i], ans, len + add_len, min_len);
        }
        dfs(dictionary, word, n + 1, abbr + to_string(n - left), ans, len + 1, min_len);
    }

    bool check(const string t, const string& s)
    {
        int nt = t.size(), ns = s.size();
        int it = 0, is = 0;
        while(is < ns && it < nt)
        {
            if(t[it] >= '0' && t[it] <= '9')
            {
                if(t[it] == '0')
                    return false;
                int j = it;
                while(j < nt && t[j] >= '0' && t[j] <= '9')
                    ++j;
                stringstream ss;
                ss << t.substr(it, j - it);
                int len;
                ss >> len;
                it = j;
                is += len;
            }
            else
            {
                if(t[it] != s[is])
                    return false;
                ++is;
                ++it;
            }
        }
        return is == ns && it == nt;
    }
};


