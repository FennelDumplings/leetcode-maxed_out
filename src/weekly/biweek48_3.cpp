
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        sort(coins.begin(), coins.end());
        int cur = 0;
        for(int i: coins)
        {
            if(i - cur > 1)
                return cur + 1;
            cur += i;
        }
        return cur + 1;
    }
};
