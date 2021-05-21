
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        using ll = long long;
        const int MOD = 1e9 + 7;
        int ans = 0;
        int i = 0;
        while(i < n)
        {
            // 按范围枚举分母 nums[i]
            int li = i, ri = i;
            while(ri < n && nums[ri] == nums[li])
                ++ri;
            int l = 0;
            int p = 0;
            while(l < n)
            {
                // 按范围枚举分子 nums[j]
                int t = nums[l] / nums[i];
                // t <= nums[j] / nums[i] < t + 1
                // t * nums[i] <= nums[j] < (t + 1) * nums[i]
                // 在 nums[j..n-1] 中找到大于等于 (t + 1) * nums[i] 的最小的数的位置
                int r = lower_bound(nums.begin() + l, nums.end(), (t + 1) * nums[i]) - nums.begin();
                // [l, r) 均对答案贡献 t
                p = (p + t * (ll)(r - l)) % MOD;
                l = r;
            }
            ans = (ans + (ll)(ri - li) * p) % MOD;
            i = ri;
        }
        return ans;
    }
};
