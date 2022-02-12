
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if(n == k)
            return nums[n - 1] - nums[0];
        int ans = nums[n - 1] - nums[0];
        for(int i = k - 1; i < n; ++i)
            ans = min(ans, nums[i] - nums[i - k + 1]);
        return ans;
    }
};
