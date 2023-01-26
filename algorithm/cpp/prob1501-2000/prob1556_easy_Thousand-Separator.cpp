// prob1556: Thousand Separator

/*
 * https://leetcode-cn.com/problems/thousand-separator/
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string thousandSeparator(int n) {
        string s;
        if(n == 0)
            s += '0';
        while(n)
        {
            s += '0' + n % 10;
            n /= 10;
        }
        int m = s.size();
        string result;
        int i = 0;
        while(i < m)
        {
            result += s[i];
            ++i;
            if(i % 3 == 0)
                result += '.';
        }
        if(result.back() == '.')
            result.pop_back();
        reverse(result.begin(), result.end());
        return result;
    }
};
