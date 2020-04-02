// prob29: Divide Two Integers

/*
 * Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.
 * Return the quotient after dividing dividend by divisor.
 * The integer division should truncate toward zero.
 */

/*
 * Example 1:
 * Input: dividend = 10, divisor = 3
 * Output: 3
 * Example 2:
 * Input: dividend = 7, divisor = -3
 * Output: -2
 */

/*
 * Note:
 * Both dividend and divisor will be 32-bit signed integers.
 * The divisor will never be 0.
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem,
 * assume that your function returns 231 − 1 when the division result overflows.
 */

#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        // dividor 不为零
        if(dividend == 0) return 0;
        if(divisor == INT_MIN)
        {
            if(dividend == INT_MIN)
                return 1;
            else
                return 0;
        }
        if(dividend == INT_MIN)
        {
            if(divisor > 0)
                return -1 - _divide(-(dividend + divisor), divisor);
            else if(divisor == -1)
                return INT_MAX;
            else
                return 1 + _divide(-(dividend - divisor), -divisor);
        }
        // [-(2^31 - 1) .. 0 .. 2^31 - 1]
        if(dividend > 0 && divisor < 0) return -_divide(dividend, -divisor);
        else if(dividend < 0 && divisor > 0) return -_divide(-dividend, divisor);
        else if (dividend < 0 && divisor < 0) return _divide(-dividend, -divisor);
        else return _divide(dividend, divisor);
    }

private:
    int _divide(int dividend, int divisor)
    {
        // dividend 和 divisor 均大于 0
        // 最多有多少个 dividor 相加，和小于等于 dividend
        if(dividend < divisor) return 0;

        stack<pair<int, int>> st;
        int result = 0;

        int div = divisor; // 当前轮次divisor
        int iter = 1; // 当前轮次往result里增加的dividor个数
        int remainder = dividend; // 当前轮次的和要满足的上界
        remainder = remainder - divisor;
        result += iter;
        st.push(pair<int, int>(divisor, 1));
        while(remainder >= 0 && INT_MAX - div >= div)
        {
            div = div + div; // 当前轮次考虑的面值
            iter = iter + iter; // 当前轮次考虑的面值相当于原始面值的倍数
            if(remainder - div >= 0)
            {
                result += iter;
                st.push(pair<int, int>(div, iter));
                remainder -= div;
            }
            else
                break;
        }
        while(!st.empty())
        {
            pair<int, int> top_item = st.top();
            st.pop();
            div = top_item.first;
            iter = top_item.second;
            while(remainder - div >= 0)
            {
                result += iter;
                remainder -= div;
            }
        }
        return result;
    }
};

// 利用移位
// 边界条件处理一样
class Solution_2 {
public:
    int divide(int dividend, int divisor) {
        // dividor 不为零
        if(dividend == 0) return 0;
        if(divisor == INT_MIN)
        {
            if(dividend == INT_MIN)
                return 1;
            else
                return 0;
        }
        if(dividend == INT_MIN)
        {
            if(divisor > 0)
                return -1 - _divide(-(dividend + divisor), divisor);
            else if(divisor == -1)
                return INT_MAX;
            else
                return 1 + _divide(-(dividend - divisor), -divisor);
        }
        // [-(2^31 - 1) .. 0 .. 2^31 - 1]
        if(dividend > 0 && divisor < 0) return -_divide(dividend, -divisor);
        else if(dividend < 0 && divisor > 0) return -_divide(-dividend, divisor);
        else if (dividend < 0 && divisor < 0) return _divide(-dividend, -divisor);
        else return _divide(dividend, divisor);
    }

private:
    int _divide(int dividend, int divisor) {
        if(dividend < divisor) return 0;

        int res = 0;

        int div = divisor;
        int iter = 1;
        dividend -= div;
        res += iter;
        // 两个循环类似进栈阶段和出栈阶段
        while(dividend >= div && INT_MAX - div >= div && dividend > (div << 1))
        {
            div = div << 1;
            iter = iter << 1;
            dividend -= div;
            res += iter;
        }
        while(div > 0)
        {
            while(dividend - div >= 0)
            {
                res += iter;
                dividend -= div;
            }
            div = div >> 1;
            iter = iter >> 1;
        }
        return res;
    }
};

