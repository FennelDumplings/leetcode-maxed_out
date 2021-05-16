#include <vector>

using namespace std;

class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for(int i = 0; i <= (1 << n) - 1; ++i)
        {
            int sum = 0;
            for(int j = 0; j < n; ++j)
                if(i >> j & 1)
                    sum ^= nums[j];
            ans += sum;
        }
        return ans;
    }
};
