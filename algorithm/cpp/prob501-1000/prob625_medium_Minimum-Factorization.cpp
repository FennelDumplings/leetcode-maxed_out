// prob625: Minimum Factorization

/*
 * https://leetcode-cn.com/problems/minimum-factorization/
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int smallestFactorization(int a) {
        if(a == 1)
            return 1;
        using ll = long long;
        vector<int> cnts(10);
        for(int i = 9; i >= 2; --i)
        {
            while(a % i == 0)
            {
                a /= i;
                ++cnts[i];
            }
        }
        if(a != 1)
            return 0;
        ll ans = 0;
        for(int i = 2; i <= 9; ++i)
        {
            while(cnts[i] > 0)
            {
                ans *= 10;
                ans += i;
                if(ans > INT_MAX)
                    return 0;
                --cnts[i];
            }
        }
        return ans;
    }
};
