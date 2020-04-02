// prob1175: Bulb Switcher III

/*
 * There is a room with n bulbs, numbered from 1 to n, arranged in a row from left to right. Initially, all the bulbs are turned off.
 * At moment k (for k from 0 to n - 1), we turn on the light[k] bulb. A bulb change color to blue only if it is on and all the
 * previous bulbs (to the left) are turned on too.
 * Return the number of moments in which all turned on bulbs are blue.
 */

/*
 * Constraints:
 * n == light.length
 * 1 <= n <= 5 * 10^4
 * light is a permutation of  [1, 2, ..., n]
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numTimesAllBlue(vector<int>& light) {
        int n = light.size();
        int num_opened = 0;
        int min_closed = 1;
        vector<bool> opened(n + 1, false);
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            opened[light[i]] = true;
            ++num_opened;
            if(light[i] == min_closed)
            {
                ++min_closed;
                while(opened[min_closed])
                    ++min_closed;
            }
            if(min_closed == num_opened + 1)
                ++ans;
        }
        return ans;
    }
};
