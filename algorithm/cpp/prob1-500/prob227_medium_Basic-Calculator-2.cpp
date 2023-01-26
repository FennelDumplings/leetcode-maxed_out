// prob227: Basic Calculator II

/*
 * Implement a basic calculator to evaluate a simple expression string.
 * The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.
 */

/*
 * Example 1:
 * Input: "3+2*2"
 * Output: 7
 * Example 2:
 * Input: " 3/2 "
 * Output: 1
 * Example 3:
 * Input: " 3+5 / 2 "
 * Output: 5
 */

/*
 * Note:
 * You may assume that the given expression is always valid.
 * Do not use the eval built-in library function.
 */

#include <string>
#include <sstream>
#include <stack>

using namespace std;

class Solution_2 {
public:
    int calculate(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        int iter = 0;
        stack<char> st_symbol;
        stack<int> st_num;
        while(iter < n)
        {
            while(iter < n && s[iter] == ' ') ++iter;
            if(iter == n) break;
            if(s[iter] == '+' || s[iter] == '-' || s[iter] == '*' || s[iter] == '/')
            {
                st_symbol.push(s[iter]);
                ++iter;
                continue;
            }
            int right = iter;
            while(right < n && s[right] >= '0' && s[right] <= '9') ++right;
            int num;
            stringstream ss;
            ss << s.substr(iter, right - iter);
            ss >> num;
            if(!st_symbol.empty() && (st_symbol.top() == '*' || st_symbol.top() == '/'))
            {
                if(st_symbol.top() == '*')
                    num = num * st_num.top();
                else
                    num = st_num.top() / num;
                st_num.pop();
                st_symbol.pop();
            }
            if(!st_symbol.empty() && (st_symbol.top() == '-'))
            {
                num = -num;
                st_symbol.pop();
                st_symbol.push('+');
            }
            st_num.push(num);
            iter = right;
        }
        while(!st_symbol.empty())
        {
            int num2 = st_num.top();
            st_num.pop();
            int num1 = st_num.top();
            st_num.pop();
            int num = num1 + num2;
            st_num.push(num);
            st_symbol.pop();
        }
        return st_num.top();
    }
};


class Solution {
public:
    int calculate(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        int iter = 0;
        // stack<char> st_symbol;
        char prev_symbol = ' ';
        stack<int> st_num;
        while(iter < n)
        {
            while(iter < n && s[iter] == ' ') ++iter;
            if(iter == n) break;
            if(s[iter] == '+' || s[iter] == '-' || s[iter] == '*' || s[iter] == '/')
            {
                prev_symbol = s[iter];
                // st_symbol.push(s[iter]);
                ++iter;
                continue;
            }
            int num = 0;
            while(iter < n && s[iter] >= '0' && s[iter] <= '9')
            {
                num += s[iter] - '0';
                num *= 10;
                ++iter;
            }
            if(prev_symbol == '*')
            {
                num = num * st_num.top();
                st_num.pop();
            }
            if(prev_symbol == '/')
            {
                num = st_num.top() / num;
                st_num.pop();
            }
            if(prev_symbol == '-')
                num = -num;
            prev_symbol = ' ';
            st_num.push(num);
        }
        int result = 0;
        while(!st_num.empty())
        {
            result += st_num.top();
            st_num.pop();
        }
        return result;
    }
};
