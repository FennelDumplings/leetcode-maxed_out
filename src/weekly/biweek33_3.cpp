
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        bool flag = true;
        while(flag)
        {
            flag = false;
            for(int i = 0; i < n; ++i)
            {
                if(nums[i] > 0)
                    flag = true;
                if(nums[i] & 1)
                {
                    --nums[i];
                    ++ans;
                }
            }
            bool flag2 = false;
            for(int i = 0; i < n; ++i)
            {
                if(nums[i] > 0)
                {
                    flag2 = true;
                    nums[i] /= 2;
                }
            }
            if(flag2)
                ++ans;
        }
        return ans;
    }
};
