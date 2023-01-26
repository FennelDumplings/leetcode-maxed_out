// prob394: Decode String

/*
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.
 * Note that k is guaranteed to be a positive integer.
 * You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
 * Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k.
 * For example, there won't be input like 3a or 2[4].
 */

/*
 * Examples:
 * s = "3[a]2[bc]", return "aaabcbc".
 * s = "3[a2[c]]", return "accaccacc".
 * s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
 */

#include <string>
#include <sstream>
#include <stack>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        if(s.empty()) return "";
        string result;
        int pos = 0;
        return dfs(s, pos);
    }

private:
    string dfs(const string& s, int& pos)
    {
        int n = s.size();
        string res;
        int multi = 0;
        while(pos < n)
        {
            if(s[pos] >= '0' && s[pos] <= '9')
            {
                multi = multi * 10 + (s[pos] - '0');
                ++pos;
                continue;
            }
            if(s[pos] == '[')
            {
                ++pos;
                string tmp = dfs(s, pos);
                for(int i = 1; i <= multi; ++i)
                    res += tmp;
                multi = 0;
                continue;
            }
            if(s[pos] == ']')
            {
                ++pos;
                return res;
            }
            res += s[pos];
            ++pos;
        }
        return res;
    }
};

// 栈
class Solution_2 {
public:
    string decodeString(string s) {
        if(s.empty()) return "";
        using PSI = pair<string, int>;
        stack<PSI> st;
        string res;
        int multi = 0;
        for(char c: s)
        {
            if(c >= '0' && c <= '9')
            {
                multi = multi * 10 + (c - '0');
                continue;
            }
            if(c == '[')
            {
                st.push(PSI(res, multi));
                res = "";
                multi = 0;
                continue;
            }
            if(c == ']')
            {
                string prev_str = st.top().first;
                int prev_multi = st.top().second;
                st.pop();
                string tmp;
                for(int i = 1; i <= prev_multi; ++i)
                    tmp += res;
                res = prev_str + tmp;
                continue;
            }
            res += c;
        }
        return res;
    }
};

// 栈
class Solution_2 {
public:
    string decodeString(string s) {
        if(s.empty()) return "";
        using PSI = pair<string, int>;
        stack<PSI> st;
        string res;
        int multi = 0;
        for(char c: s)
        {
            if(c >= '0' && c <= '9')
            {
                multi = multi * 10 + (c - '0');
                continue;
            }
            if(c == '[')
            {
                st.push(PSI(res, multi));
                res = "";
                multi = 0;
                continue;
            }
            if(c == ']')
            {
                string prev_str = st.top().first;
                int prev_multi = st.top().second;
                st.pop();
                string tmp;
                for(int i = 1; i <= prev_multi; ++i)
                    tmp += res;
                res = prev_str + tmp;
                continue;
            }
            res += c;
        }
        return res;
    }
};
