// prob282: Expression Add Operators

/*
 * Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.
 */

/*
 * Example 1:
 * Input: num = "123", target = 6
 * Output: ["1+2+3", "1*2*3"]
 * Example 2:
 * Input: num = "232", target = 8
 * Output: ["2*3+2", "2+3*2"]
 * Example 3:
 * Input: num = "105", target = 5
 * Output: ["1*0+5","10-5"]
 * Example 4:
 * Input: num = "00", target = 0
 * Output: ["0+0", "0-0", "0*0"]
 * Example 5:
 * Input: num = "3456237490", target = 9191
 * Output: []
 */

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        if(num.empty()) return vector<string>();
        vector<string> result;
        string item;
        item += num[0];
        int new_num = num[0] - '0';
        bool zero = num[0] == '0';
        dfs(num, 0, target, item, result, 0, new_num, 0, 1, 0, zero);
        return result;
    }

private:
    using ll = long long;

    void dfs(const string& num, int pos, int target, string& item, vector<string>& result,
            ll num1, ll num2, ll num3, int op1, int op2, bool zero)
    {
        // num[pos] 已经加入 item
        // op1 = 1: 加法
        // op1 = 2: 减法
        // op2 = 1: 乘A, num3 为活动数字
        // op2 = 0: 无乘法, nums2 为活动数字
        int n = num.size();
        if(pos == n - 1)
        {
            if(op2)
                num2 *= num3;
            if(op1 == 1)
                num1 += num2;
            else
                num1 -= num2;
            if(num1 == target)
                result.push_back(item);
            return;
        }

        // num[pos] 与 num[pos+1] 之间可能是 空格, +, - , *
        ++pos;
        int new_num = num[pos] - '0';
        bool new_zero = new_num == 0;
        // 1. 空格
        if(!zero) // 活动数字不为 0 , 才可以根空格
        {
            item += num[pos];
            if(op2)
                dfs(num, pos, target, item, result, num1, num2, num3 * 10 + new_num, op1, op2, zero);
            else
                dfs(num, pos, target, item, result, num1, num2 * 10 + new_num, num3, op1, op2, zero);
            item.pop_back();
        }
        // *, +, 或 -
        // 无论是*,+,-,栈里有乘号都必须先处理
        if(op2)
            num2 *= num3;
        // 2. *
        item += '*';
        item += num[pos];
        dfs(num, pos, target, item, result, num1, num2, new_num, op1, 1, new_zero);
        item.pop_back();
        item.pop_back();
        // 无论是+,-,栈里的+/-都必须先处理
        if(op1 == 1)
            num1 += num2;
        else if(op1 == 2)
            num1 -= num2;
        // 3. +
        item += '+';
        item += num[pos];
        dfs(num, pos, target, item, result, num1, new_num, 0, 1, 0, new_zero);
        item.pop_back();
        item.pop_back();
        // 4. -
        item += '-';
        item += num[pos];
        dfs(num, pos, target, item, result, num1, new_num, 0, 2, 0, new_zero);
        item.pop_back();
        item.pop_back();
    }
};
