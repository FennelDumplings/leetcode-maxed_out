#include <vector>

using namespace std;

class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int n = nums.size();
        int num_maxset = 0;
        int max_value = 0;
        for(int s = 1; s < (1 << n); ++s)
        {
            int value = 0;
            for(int i = 0; i < n; ++i)
            {
                if(s >> i & 1)
                    value |= nums[i];
            }
            if(value > max_value)
            {
                max_value = value;
                num_maxset = 1;
            }
            else if(value == max_value)
                ++num_maxset;
        }
        return num_maxset;
    }
};
