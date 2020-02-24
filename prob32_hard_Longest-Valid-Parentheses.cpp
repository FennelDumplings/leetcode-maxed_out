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
