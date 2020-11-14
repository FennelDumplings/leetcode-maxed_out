// prob1134: Armstrong Number

/*
 * https://leetcode-cn.com/problems/armstrong-number/
 */

#include <cmath>

using namespace  std;

class Solution {
public:
    bool isArmstrong(int N) {
        int k = 0;
        int n = N;
        while(n)
        {
            n /= 10;
            ++k;
        }
        int x = 0;
        n = N;
        while(n)
        {
            x += pow(n % 10, k);
            n /= 10;
        }
        return x == N;
    }
};
