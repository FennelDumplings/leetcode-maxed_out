// prob1541: Minimum Insertions to Balance a Parentheses String

/*
 * https://leetcode-cn.com/problems/minimum-insertions-to-balance-a-parentheses-string/
 */


#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        stack<int> st_l, st_r;
        for(int i = 0; i < n; ++i)
        {
            char &ch = s[i];
            if(ch == '(')
            {
                st_l.push(i);
            }
            else
            {
                if(!st_l.empty()  && !st_r.empty() && st_r.top() == i - 1)
                {
                    st_l.pop();
                    st_r.pop();
                }
                else
                    st_r.push(i);
            }
        }
        string remain;
        int ans = 0;
        while(!st_l.empty() && !st_r.empty())
        {
            if(st_l.top() < st_r.top())
            {
                int i = st_r.top();
                remain += s[i];
                st_r.pop();
                if(!st_r.empty() && st_r.top() == i - 1)
                {
                    ans += 1;
                    remain.pop_back();
                    st_r.pop();
                }
            }
            else
            {
                if(!remain.empty() && remain.back() == ')')
                {
                    ans += 1;
                    remain.pop_back();
                }
                else
                {
                    remain += s[st_l.top()];
                }
                st_l.pop();
            }
        }
        while(!st_l.empty())
        {
            if(!remain.empty() && remain.back() == ')')
            {
                ans += 1;
                remain.pop_back();
            }
            else
            {
                remain += s[st_l.top()];
            }
            st_l.pop();
        }
        while(!st_r.empty())
        {
            int i = st_r.top();
            remain += s[i];
            st_r.pop();
            if(!st_r.empty() && st_r.top() == i - 1)
            {
                ans += 1;
                remain.pop_back();
                st_r.pop();
            }
        }
        ans += remain.size() * 2;
        return ans;
    }
};
