
#include <vector>

using namespace std;


class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        int ans = nums[1];
        while(i < n)
        {
            int sum = nums[i];
            int j = i + 1;
            while(j < n && nums[j - 1] < nums[j])
            {
                sum += nums[j];
                ++j;
            }
            ans = max(ans, sum);
            ++i;
        }
        return ans;
    }
};
