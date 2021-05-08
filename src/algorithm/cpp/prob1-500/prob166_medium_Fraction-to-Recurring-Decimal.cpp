// prob166: Fraction to Recurring Decimal

/*
 * Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
 * If the fractional part is repeating, enclose the repeating part in parentheses.
 */

/*
 * Example 1:
 * Input: numerator = 1, denominator = 2
 * Output: "0.5"
 * Example 2:
 * Input: numerator = 2, denominator = 1
 * Output: "2"
 * Example 3:
 * Input: numerator = 2, denominator = 3
 * Output: "0.(6)"
 */

#include <string>
#include <climits>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if(numerator == 0) return "0";
        if(numerator < 0 && denominator < 0)
        {
            if(denominator == INT_MIN || numerator == INT_MIN)
                return fractionToDecimal(-(long long)numerator, -(long long)denominator);
            return fractionToDecimal(-numerator, -denominator);
        }
        if(numerator < 0)
        {
            if(numerator == INT_MIN)
                return '-' + fractionToDecimal(-(long long)numerator, (long long)denominator);
            return '-' + fractionToDecimal(-numerator, denominator);
        }
        if(denominator < 0)
        {
            if(denominator == INT_MIN)
                return '-' + fractionToDecimal((long long)numerator, -(long long)denominator);
            return '-' + fractionToDecimal(numerator, -denominator);
        }
        string result;
        int p = numerator / denominator;
        int q = numerator % denominator;
        result += to_string(p);
        if(q == 0) return result;
        result += '.';
        unordered_map<int, int> mapping;
        while(q != 0)
        {
            int n = q * 10;
            if(mapping[n] != 0)
            {
                result.insert(mapping[n], 1, '(');
                result += ')';
                break;
            }
            mapping[n] = (int)result.size();
            p = n / denominator;
            q = n % denominator;
            result += to_string(p);
        }
        return result;
    }

    string fractionToDecimal(long long numerator, long long denominator) {
        string result;
        long long p = numerator / denominator;
        long long q = numerator % denominator;
        result += to_string(p);
        if(q == 0) return result;
        result += '.';
        unordered_map<long long, int> mapping;
        while(q != 0)
        {
            long long n = (long long)q * 10;
            if(mapping[n] != 0)
            {
                result.insert(mapping[n], 1, '(');
                result += ')';
                break;
            }
            mapping[n] = (int)result.size();
            p = n / denominator;
            q = n % denominator;
            result += to_string(p);
        }
        return result;
    }
};
