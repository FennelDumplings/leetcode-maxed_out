// prob842: Split Array into Fibonacci Sequence

/*
 * Given a string S of digits, such as S = "123456579", we can split it into a Fibonacci-like sequence [123, 456, 579].
 * Formally, a Fibonacci-like sequence is a list F of non-negative integers such that:
 * 0 <= F[i] <= 2^31 - 1, (that is, each integer fits a 32-bit signed integer type);
 * F.length >= 3;
 * and F[i] + F[i+1] = F[i+2] for all 0 <= i < F.length - 2.
 * Also, note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.
 * Return any Fibonacci-like sequence split from S, or return [] if it cannot be done.
 */

/*
 * Example 1:
 * Input: "123456579"
 * Output: [123,456,579]
 * Example 2:
 * Input: "11235813"
 * Output: [1,1,2,3,5,8,13]
 * Example 3:
 * Input: "112358130"
 * Output: []
 * Explanation: The task is impossible.
 * Example 4:
 * Input: "0123"
 * Output: []
 * Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
 * Example 5:
 * Input: "1101111"
 * Output: [110, 1, 111]
 * Explanation: The output [11, 0, 11, 11] would also be accepted.
 */

/*
 * Note:
 * 1 <= S.length <= 200
 * S contains only digits.
 */

#include <vector>
#include <string>
#include <climits>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<int> splitIntoFibonacci(string S) {
        int n = S.size();
        if(n < 3) return vector<int>();
        string str1, str2;
        int left = 0;
        vector<int> result;
        for(int iter1 = left + 1; iter1 < n && iter1 - left <= 10; ++iter1)
        {
            if(S[0] == '0' && iter1 > 1) break;
            str1 = S.substr(0, iter1 - left);
            ll num1;
            stringstream ss;
            ss << str1;
            ss >> num1;
            if(num1 > INT_MAX) break;
            for(int iter2 = iter1 + 1; iter2 < n && iter2 - iter1 <= 10; ++iter2)
            {
                if(S[iter1] == '0' && iter1 > iter1 + 1) break;
                str2 = S.substr(iter1, iter2 - iter1);
                ll num2;
                stringstream ss;
                ss << str2;
                ss >> num2;
                if(num2 > INT_MAX) break;
                result.clear();
                result.push_back(num1);
                result.push_back(num2);
                if(_check(S, iter2, n, (int)num1, (int)num2, result))
                    return result;
            }
        }
        return vector<int>();
    }

private:
    using ll = long long;
    bool _check(const string& S, int pos, int n, int prev1, int prev2, vector<int>& result)
    {
        if(pos == n)
            return true;

        ll nxt = (ll)prev1 + prev2;
        if(nxt > INT_MAX) return false;

        string str = to_string(nxt);
        int iter = pos;
        while(iter < n && iter - pos < (int)str.size())
        {
            if(S[iter] != str[iter - pos])
                return false;
            ++iter;
        }
        if(iter - pos < (int)str.size())
            return false;

        result.push_back(nxt);
        return _check(S, iter, n, prev2, nxt, result);
    }
};
