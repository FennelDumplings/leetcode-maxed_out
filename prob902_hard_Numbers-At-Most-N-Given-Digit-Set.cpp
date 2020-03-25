// prob902: Numbers At Most N Given Digit Set

/*
 * We have a sorted set of digits D, a non-empty subset of {'1','2','3','4','5','6','7','8','9'}.  (Note that '0' is not included.)
 * Now, we write numbers using these digits, using each digit as many times as we want.  For example, if D = {'1','3','5'},
 * we may write numbers such as '13', '551', '1351315'.
 * Return the number of positive integers that can be written (using the digits of D) that are less than or equal to N.
 */

/*
 * Example 1:
 * Input: D = ["1","3","5","7"], N = 100
 * Output: 20
 * Explanation:
 * The 20 numbers that can be written are:
 * 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
 * Example 2:
 * Input: D = ["1","4","9"], N = 1000000000
 * Output: 29523
 * Explanation:
 * We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
 * 81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
 * 2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
 * In total, this is 29523 integers that can be written using the digits of D.
 */

/*
 * Note:
 * D is a subset of digits '1'-'9' in sorted order.
 * 1 <= N <= 10^9
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        int d = D.size();
        unordered_set<char> setting;
        for(string c: D) setting.insert(c[0]);
        vector<int> lessthan(10, 0); // lessthan[i]: D 中小于 i 的数字的个数, 1 <= i <= 9
        vector<bool> equal(10, false); // equal[i]: i 是否在 D 中, 1 <= i <= 9
        for(int i = 1; i <= 9; ++i)
            if(setting.find('0' + i) != setting.end())
                equal[i] = true;
        for(int i = 2; i <= 9; ++i)
        {
            lessthan[i] = lessthan[i - 1];
            if(equal[i - 1])
                ++lessthan[i];
        }
        vector<int> digits = _num_digit(N);
        int n = digits.size();
        int result = _check(n, d, digits, lessthan, equal);
        for(int i = 1; i <= n - 1; ++i)
            result += pow(d, i);
        return result;
    }

private:
    int _check(int k, int d, vector<int>& digits, vector<int>& lessthan, vector<bool>& equal)
    {
        // k 位数, 且小于等于 N 的前 k 位的选法
        if(k < 1) return 1;
        int result = 0;
        int cur = digits[k - 1];
        result += pow(d, k - 1) * lessthan[cur];
        if(equal[cur])
            result += _check(k - 1, d, digits, lessthan, equal);
        return result;
    }

    vector<int> _num_digit(int N)
    {
        vector<int> result;
        while(N)
        {
            result.push_back(N % 10);
            N /= 10;
        }
        return result;
    }
};
