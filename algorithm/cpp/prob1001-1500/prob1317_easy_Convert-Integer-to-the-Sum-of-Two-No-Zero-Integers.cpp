// prob1317: Convert Integer to the Sum of Two No-Zero Integers

/*
 * https://leetcode-cn.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        for(int i = 1; i <= n / 2; ++i)
        {
            if(check(i) && check(n - i))
                return {i, n - i};
        }
        return {-1, -1};
    }

private:
    bool check(int x)
    {
        while(x)
        {
            if(x % 10 == 0)
                return false;
            x /= 10;
        }
        return true;
    }
};
