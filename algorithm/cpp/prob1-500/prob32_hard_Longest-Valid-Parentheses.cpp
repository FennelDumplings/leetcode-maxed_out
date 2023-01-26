// prob32: Longest Valid Parentheses

/*
 * Given a string containing just the characters '(' and ')',
 * find the length of the longest valid (well-formed) parentheses substring.
 */

/*
 * Example 1:
 * Input: "(()"
 * Output: 2
 * Explanation: The longest valid parentheses substring is "()"
 * Example 2:
 * Input: ")()())"
 * Output: 4
 * Explanation: The longest valid parentheses substring is "()()"
 */

#include <string>
#include <stack>
#include <vector>

using namespace std;


// 三种解法
// https://leetcode-cn.com/problems/longest-valid-parentheses/solution/zui-chang-you-xiao-gua-hao-by-leetcode/
// 1. 栈，保存 ( 对应的下标，遇到 ) 出栈时由下标差得长度
class Solution {
public:
    int longestValidParentheses(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        stack<int > st;
        st.push(-1);
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            if(s[i] == '(')
                st.push(i);
            else
            {
                st.pop();
                if(st.empty())
                    st.push(i);
                else
                    result = max(result, i - st.top());
            }
        }
        return result;
    }
};

// 2. 用计数器记录，需要跑两次，应对 ()(() 这种 case
class Solution_2 {
public:
    int longestValidParentheses(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        int result_l2r = 0;
        int start = 0;
        int left_parentheres = 0;
        int right_parentheres = 0;
        while(start < n)
        {
            if(s[start] == '(')
                ++left_parentheres;
            else
            {
                ++right_parentheres;
                if(left_parentheres == right_parentheres)
                {
                    result_l2r = max(result_l2r, left_parentheres + right_parentheres);
                }
                else if(left_parentheres < right_parentheres)
                {
                    left_parentheres = 0;
                    right_parentheres = 0;
                }
            }
            ++start;
        }
        int result_r2l = 0;
        start = n - 1;
        left_parentheres = 0;
        right_parentheres = 0;
        while(start >= 0)
        {
            if(s[start] == ')')
                ++right_parentheres;
            else
            {
                ++left_parentheres;
                if(left_parentheres == right_parentheres)
                {
                    result_r2l = max(result_r2l, left_parentheres + right_parentheres);
                }
                else if(left_parentheres > right_parentheres)
                {
                    left_parentheres = 0;
                    right_parentheres = 0;
                }
            }
            --start;
        }
        return max(result_l2r, result_r2l);
    }
};

// 3. DP
// dp[i] := 以 i 结尾的最长有效长度
// 初始化至少两个值 dp[0] = 0, dp[1]
// 只更新 s[i] = ')' 的情况，s[i] = '(' dp[i] = 0
// s[i] = ')' 有两种情况
// 1. '()' s[i] = ')' s[i - 1] = '(' dp[i] = dp[i - 2] + 2
// 2. '))' s[i] = ')' s[i - 1] = ')' dp[i] = dp[i - 1] + 2 + dp[i - dp[i - 1] - 2]
class Solution_3 {
public:
    int longestValidParentheses(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        if(n == 1) return 0;
        vector<int> dp(n, 0);
        if(s[0] == '(' && s[1] == ')') dp[1] = 2;
        int result = dp[1];
        for(int i = 2; i < n; ++i)
        {
            if(s[i] == ')')
            {
                if(s[i - 1] == '(')
                    dp[i] = dp[i - 2] + 2;
                else
                {
                    if(i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                    {
                        dp[i] = dp[i - 1] + 2;
                        if(i - dp[i - 1] - 2 >= 0)
                            dp[i] += dp[i - dp[i - 1] - 2];
                    }
                }
            }
            result = max(result, dp[i]);
        }
        return result;
    }
};
