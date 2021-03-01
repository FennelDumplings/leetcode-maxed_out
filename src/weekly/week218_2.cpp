#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n  = nums.size();
        int ans = 0;
        int i = 0, j = n - 1;
        while(i < j)
        {
            if(nums[i] + nums[j] == k)
            {
                ++ans;
                ++i;
                --j;
            }
            else if(nums[i] + nums[j] < k)
                ++i;
            else
                --j;
        }
        return ans;
    }
};
