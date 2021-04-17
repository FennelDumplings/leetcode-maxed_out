// prob1405: Longest Happy String

/*
 * https://leetcode-cn.com/problems/longest-happy-string/
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Char
{
    char ch;
    int cnt;
    Char(char ch, int cnt):ch(ch),cnt(cnt){}
};

struct Cmp
{
    bool operator()(const Char& c1, const Char& c2)
    {
        return c1.cnt < c2.cnt;
    }
};

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        string ans;
        Char A('a', a);
        Char B('b', b);
        Char C('c', c);
        vector<Char> sorted = {A, B, C};
        solve(sorted, ans);
        return ans;
    }

private:
    void solve(vector<Char>& chars, string& s)
    {
        // c >= b >= a
        sort(chars.begin(), chars.end(), Cmp());
        if(chars[2].cnt == 0)
            return;
        if(chars[1].cnt == 0)
        {
            for(int i = 0; i < min(chars[2].cnt, 2); ++i)
                s += chars[2].ch;
            return;
        }
        if(chars[1].cnt == chars[2].cnt && chars[0].cnt == chars[1].cnt)
        {
            for(int i = 0; i < chars[0].cnt; ++i)
                s += "cba";
            return;
        }
        // 一定有一个小于号
        // chars[2] == chars[1] > chars[0]
        if(chars[1].cnt == chars[2].cnt)
        {
            s += chars[2].ch;
            s += chars[1].ch;
            --chars[2].cnt;
            --chars[1].cnt;
            solve(chars, s);
            return;
        }
        // chars[2] > chars[1] >= chars[0]
        s += chars[2].ch;
        s += chars[2].ch;
        s += chars[1].ch;
        --chars[2].cnt;
        --chars[2].cnt;
        --chars[1].cnt;
        solve(chars, s);
    }
};
