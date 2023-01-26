// prob856: Score of Parentheses

/*
 * Given a balanced parentheses string S, compute the score of the string based on the following rule:
 * () has score 1
 * AB has score A + B, where A and B are balanced parentheses strings.
 * (A) has score 2 * A, where A is a balanced parentheses string.
 */

/*
 * Example 1:
 * Input: "()"
 * Output: 1
 * Example 2:
 * Input: "(())"
 * Output: 2
 * Example 3:
 * Input: "()()"
 * Output: 2
 * Example 4:
 * Input: "(()(()))"
 * Output: 6
 */

/*
 * Note:
 * S is a balanced parentheses string, containing only ( and  ).
 * 2 <= S.length <= 50
 */

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int scoreOfParentheses(string S) {
        if(S.empty()) return 0;
        int n = S.size();
        stack<int> st; // '(' 的下标 l
        stack<PII> st_val; //  ')' 的下标及其对应的值(平衡子括号串的值)
        for(int i = 0; i < n; ++i)
        {
            char cur = S[i];
            if(cur == '(')
            {
                st.push(i);
            }
            else
            {
                int val;
                if(st.top() + 1 == i)
                    val = 1;
                else
                {
                    val = st_val.top().second * 2;
                    st_val.pop();
                }
                if(!st_val.empty() && st_val.top().first + 1 == st.top())
                {
                    val += st_val.top().second;
                    st_val.pop();
                }
                st_val.push(PII(i, val));
                st.pop();
            }
        }
        return st_val.top().second;
    }

private:
    using PII = pair<int, int>;
};
