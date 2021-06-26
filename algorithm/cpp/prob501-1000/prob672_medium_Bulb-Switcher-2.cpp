// prob672: Bulb Switcher II

/*
 * https://leetcode-cn.com/problems/bulb-switcher-ii/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int flipLights(int n, int m) {
        if(n == 0 || m == 0)
            return 1;
        else if(n == 1)
            return 2;
        else if(n == 2)
        {
            if(m == 1)
                return 3;
            else
                return 4;
        }
        else
        {
            if(m == 1)
                return 4;
            else if(m == 2)
                return 7;
            else
                return 8;
        }
    }
};
