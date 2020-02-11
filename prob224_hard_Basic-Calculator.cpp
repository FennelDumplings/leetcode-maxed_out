// prob: Basic Calculator

/*
 * The expression string may contain open ( and closing parentheses  ),
 * the plus + or minus sign -, non-negative integers and empty spaces .
 */

/*
 * Example 1:
 * Input: "1 + 1"
 * Output: 2
 * Example 2:
 * Input: " 2-1 + 2 "
 * Output: 3
 * Example 3:
 * Input: "(1+(4+5+2)-3)+(6+8)"
 * Output: 23
 */

#include <string>
#include <stack>
#include <sstream>

using namespace std;

// 数字的左边一定是 +- 或者 (
// +- 的左边呢一定是数字或者 ) 右边一定是数字或 (
// ) 不进栈, ( 和 数字 和 +- 进栈
// 遇到 ) 时候, 出栈直至遇到 (，然后更新 () 的计算结果进栈
// 弹出栈时，数字前面的符号只对当前数字起作用
class Solution {
public:
    int calculate(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        stack<string> st;
        //for(int i = 0; i < n; ++i)
        int i = 0;
        while(i < n)
        {
            if(s[i] == ' ')
            {
                ++i;
                continue;
            }
            if(s[i] == '(' || s[i] == '+' || s[i] == '-')
            {
                st.push(s.substr(i, 1));
                ++i;
            }
            else if(s[i] == ')')
            {
                // 涉及到出栈
                int sum = 0;
                while(true)
                {
                    string n1str = st.top();
                    st.pop();
                    string signstr = st.top();
                    st.pop();
                    if(signstr == "(")
                    {
                        sum += str2int(n1str);
                        st.push(to_string(sum));
                        break;
                    }
                    else
                    {
                        if(signstr == "+")
                            sum += str2int(n1str);
                        else
                            sum -= str2int(n1str);
                    }
                }
                ++i;
            }
            else
            {
                int l = i;
                int r = i + 1;
                while(r < n && s[r] != '(' && s[r] != ')' && s[r] != '+' && s[r] != '-')
                    ++r;
                st.push(s.substr(l, r - l));
                i = r;
            }
        }
        int result = 0;
        while(true)
        {
            string n1str = st.top();
            st.pop();
            if(st.empty())
            {
                result += str2int(n1str);
                break;
            }
            string signstr = st.top();
            st.pop();
            if(signstr == "+")
                result += str2int(n1str);
            else
                result -= str2int(n1str);
        }
        return result;
    }
private:
    int str2int(string s)
    {
        stringstream ss(s);
        int n;
        ss >> n;
        return n;
    }
};
