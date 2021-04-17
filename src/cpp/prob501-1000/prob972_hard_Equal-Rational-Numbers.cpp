// prob972: Equal Rational Numbers

/*
 * https://leetcode-cn.com/problems/equal-rational-numbers/
 */

#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

using ll = long long;

struct Fraction
{
    // 分数 x / y
    ll x, y;
    Fraction(ll x, ll y):x(x),y(y){}
    void reduction()
    {
        // 约分
        int _gcd = gcd<int>(x, y);
        x /= _gcd;
        y /= _gcd;
    }
};

int repetent(const string& S)
{
    // 有限长的串上寻找最短循环节
    int n = S.size();
    for(int i = 1; i * 2 <= n; ++i)
    {
        if(n % i != 0)
            continue;
        string p = S.substr(0, i);
        bool flag = true;
        for(int j = i; j < n; j += i)
        {
            if(S.substr(j, i) != p)
            {
                flag = false;
                break;
            }
            if(flag)
                return i;
        }
    }
    return n;
}

class Solution_2 {
public:
    bool isRationalEqual(string S, string T) {
        Fraction fracS = to_frac(S);
        Fraction fracT = to_frac(T);
        fracS.reduction();
        fracT.reduction();
        return fracS.x == fracT.x && fracS.y == fracT.y;
    }

private:

    Fraction to_frac(const string& S)
    {
        int n = S.size();
        int i = 0; // 左括号位置
        int dot_idx = -1; // 小数点位置
        int nonrepeat_len = 0; // 不循环部分的长度
        int len = 0; // 循环节长度

        ll integerPart = 0, nonRepeatingPart = 0, repeatingPart = 0;
        while(i < n && S[i] != '(')
        {
            // 整数部分
            if(S[i] == '.')
            {
                dot_idx = i;
                stringstream ss;
                ss << S.substr(0, dot_idx);
                ss >> integerPart;
            }
            ++i;
        }
        if(dot_idx == -1)
        {
            // 没有不循环小数部分
            stringstream ss;
            ss << S.substr(0, i);
            ss >> integerPart;
        }
        else if(i - dot_idx - 1 > 0)
        {
            // 不循环小数部分
            nonrepeat_len = i - dot_idx - 1;
            stringstream ss;
            ss << S.substr(dot_idx + 1, i - dot_idx - 1);
            ss >> nonRepeatingPart;
        }

        int j = i + 1; // 右括号位置
        while(j < n && S[j] != ')')
            ++j;
        if(j < n)
        {
            len = repetent(S.substr(i + 1, j - i - 1)); // 最短循环节长度
            // nonRepeatingPart 中往前找与 p 重合的部分
            string p = S.substr(i + 1, len);
            string t = S.substr(dot_idx + 1, i - dot_idx - 1);
            int idx = t.size() - 1;
            int iter = p.size() - 1;
            while(idx >= 0 && t[idx] == p[iter])
            {
                --idx;
                iter = (iter - 1 + len) % len;
            }
            // 重合部分长度，给定的循环节位置不是循环节最早出现的位置，需要调整
            int shift = nonrepeat_len - (idx + 1);
            nonrepeat_len = idx + 1;
            // 调整后的不循环小数部分长度
            if(nonrepeat_len == 0)
                nonRepeatingPart = 0;
            else
            {
                stringstream ss;
                ss << t.substr(0, nonrepeat_len);
                ss >> nonRepeatingPart;
            }
            // 调整后的循环节
            shift %= len;
            rotate(p.begin(), p.begin() + shift,  p.end());
            stringstream ss;
            ss << p;
            ss >> repeatingPart;
        }

        if(nonRepeatingPart == 0 && repeatingPart == 0)
            return Fraction(integerPart, 1);
        if(repeatingPart != 0)
        {
            // 小数转分数

            // 乘以 pow(10, len) 之后的整数，不循环小数部分，循环节
            ll new_integerPart = integerPart;
            ll new_repeatingPart = repeatingPart;
            ll new_nonRepeatingPart = nonRepeatingPart;

            new_integerPart = new_integerPart * pow(10, len);
            if(nonrepeat_len >= len)
            {
                int delta = nonrepeat_len - len;
                new_integerPart += new_nonRepeatingPart / (ll)pow(10, delta);
                new_nonRepeatingPart %= (ll)pow(10, delta);
                new_nonRepeatingPart *= pow(10, len);
                new_nonRepeatingPart += new_repeatingPart;
            }
            else
            {
                int delta = len - nonrepeat_len;
                new_integerPart += new_nonRepeatingPart * (ll)pow(10, delta);
                new_integerPart += new_repeatingPart / (ll)pow(10, nonrepeat_len);
                new_nonRepeatingPart = new_repeatingPart % (ll)pow(10, nonrepeat_len);
            }
            // 乘以 pow(10, len) 之后的数与原数相减，整数和不循环小数部分分别做差再加起来
            integerPart = new_integerPart - integerPart;
            integerPart *= pow(10, nonrepeat_len);
            nonRepeatingPart = new_nonRepeatingPart - nonRepeatingPart;
            integerPart += nonRepeatingPart;
            return Fraction(integerPart, (pow(10, len) - 1) * pow(10, nonrepeat_len));
        }
        if(nonRepeatingPart == 0)
            return Fraction(integerPart, 1);
        return Fraction(integerPart * pow(10, nonrepeat_len) + nonRepeatingPart, pow(10, nonrepeat_len));
    }
};

struct ContinuedFraction
{
    static constexpr double EPS = 1e-15;
    vector<int> vec;
    ContinuedFraction(){}
    ContinuedFraction(double S)
    {
        if(S < EPS)
        {
            vec.push_back(0);
            return;
        }
        while(true)
        {
            int a = floor(S);
            vec.push_back(a);
            S -= a;
            if(S < EPS)
                return;
            S = 1 / S;
        }
    }
};

