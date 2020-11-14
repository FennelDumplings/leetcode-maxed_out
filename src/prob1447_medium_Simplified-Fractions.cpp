// prob1447: Simplified Fractions

/*
 * https://leetcode-cn.com/problems/simplified-fractions/
 */

#include <vector>
#include <string>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<string> simplifiedFractions(int n) {
        vector<string> result;
        for(int b = 2; b <= n; ++b)
        {
            for(int a = 1; a < b; ++a)
            {
                if(a == 1 || gcd<int>(a, b) == 1)
                {
                    result.push_back(to_string(a) + '/' + to_string(b));
                }
            }
        }
        return result;
    }
};
