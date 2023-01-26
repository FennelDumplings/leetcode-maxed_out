#include <cmath>

using namespace std;

class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> sums(n + 1);
        int max_sum = 0, min_sum = 0;
        for(int i = 1; i <= n; ++i)
        {
            sums[i] = nums[i - 1] + sums[i - 1];
            max_sum = max(max_sum, sums[i]);
            min_sum = min(min_sum, sums[i]);
        }
        return max_sum - min_sum;
    }
};
