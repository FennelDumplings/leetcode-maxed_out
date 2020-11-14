// prob1362: Closest Divisors

/*
 * https://leetcode-cn.com/problems/closest-divisors/
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> closestDivisors(int num) {
        vector<int> result(2);
        int d = -1;
        int n = num + 1;
        for(int i = sqrt(n); i >= 1; --i)
        {
            if(n % i == 0)
            {
                result[0] = i;
                result[1] = n / i;
                d = abs(i - n / i);
                break;
            }
        }
        n = num + 2;
        for(int i = sqrt(n); i >= 1; --i)
        {
            if(n % i == 0)
            {
                if(abs(i - n / i) < d)
                {
                    result[0] = i;
                    result[1] = n / i;
                }
                break;
            }
        }
        return result;
    }
};
