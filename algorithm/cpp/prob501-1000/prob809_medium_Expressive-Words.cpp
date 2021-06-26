// prob809: Expressive Words

/*
 * https://leetcode-cn.com/problems/expressive-words/
 */

#include <string>
#include <vector>

using namespace std;

struct CharInfo
{
    char ch;
    int cnt;
    CharInfo():ch(' '),cnt(0){}
    CharInfo(char ch, int cnt):ch(ch),cnt(cnt){}
};

class Solution {
public:
    int expressiveWords(string S, vector<string>& words) {
        vector<CharInfo> S_info = get_info(S);
        int ans = 0;
        for(const string& w: words)
        {
            vector<CharInfo> w_info = get_info(w);
            if(check(S_info, w_info))
                ++ans;
        }
        return ans;
    }

private:
    bool check(const vector<CharInfo>& s_info, const vector<CharInfo>& w_info)
    {
        int ns = s_info.size(), nw = w_info.size();
        if(ns != nw)
            return false;
        for(int i = 0; i < ns; ++i)
        {
            if(s_info[i].ch != w_info[i].ch)
                return false;
            if(s_info[i].cnt <= 2 && w_info[i].cnt != s_info[i].cnt)
                return false;
            if(s_info[i].cnt >= 3 && w_info[i].cnt > s_info[i].cnt)
                return false;
        }
        return true;
    }

    vector<CharInfo> get_info(const string& s)
    {
        int n = s.size();
        int i = 0;
        vector<CharInfo> result;
        while(i < n)
        {
            char ch = s[i];
            int j = i + 1;
            while(j < n && s[j] == ch)
                ++j;
            int cnt = j - i;
            result.emplace_back(ch, cnt);
            i = j;
        }
        return result;
    }
};
