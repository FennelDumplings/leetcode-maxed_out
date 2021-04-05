#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int purchasePlans(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int l = 0, r = n - 1;
        using ll = long long;
        const int MOD = 1e9 + 7;
        ll ans = 0;
        while(l < r)
        {
            if(nums[l] + nums[r] <= target)
            {
                // [l..r] 以 l 开头可以有 r - l 个
                ans += r - l;
                ++l;
            }
            else
            {
                // 以
                --r;
            }
        }
        return ans % MOD;
    }
};
