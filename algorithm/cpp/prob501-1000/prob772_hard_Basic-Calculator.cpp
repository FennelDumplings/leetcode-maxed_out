// prob772: Basic Calculator III

/*
 * https://leetcode-cn.com/problems/basic-calculator-iii/
 */

#include <unordered_map>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

using ll = long long;

class Solution {
public:
    int calculate(string s) {
        stack<char> st_symbol;
        stack<ll> st_num;
        int n = s.size();
        int i = 0;
        while(i < n)
        {
            if(s[i] == ' ')
            {
                ++i;
                continue;
            }
            if(s[i] == '(')
                st_symbol.push('(');
            else if(s[i] == ')')
            {
                while(st_symbol.top() != '(')
                {
                    calc_st_top(st_symbol, st_num);
                }
                st_symbol.pop();
            }
            else if(s[i] >= '0' && s[i] <= '9')
            {
                int j = i + 1;
                while(j < n && s[j] >= '0' && s[j] <= '9')
                    ++j;
                stringstream ss;
                ss << s.substr(i, j - i);
                ll num;
                ss >> num;
                st_num.push(num);
                i = j - 1;
            }
            else
            {
                char symbol = s[i];
                while(!st_symbol.empty() && symbol_priority[st_symbol.top()] >= symbol_priority[symbol])
                {
                    calc_st_top(st_symbol, st_num);
                }
                st_symbol.push(symbol);
            }
            ++i;
        }
        while(!st_symbol.empty())
        {
            calc_st_top(st_symbol, st_num);
        }
        return st_num.top();
    }

private:
    unordered_map<char, int> symbol_priority = {
        {'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
    };

    void calc_st_top(stack<char>& st_symbol, stack<ll>& st_num)
    {
        char op = st_symbol.top();
        st_symbol.pop();
        ll num_right = st_num.top();
        st_num.pop();
        ll num_left = st_num.top();
        st_num.pop();
        ll res = calc(num_left, num_right, op);
        st_num.push(res);
    }

    ll calc(ll num_left, ll num_right, char op)
    {
        if(op == '+')
            return num_left + num_right;
        if(op == '-')
            return num_left - num_right;
        if(op == '*')
            return num_left * num_right;
        else
            return num_left / num_right;
    }
};
