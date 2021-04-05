#include <set>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        using ll = long long;
        const int MOD = 1e9 + 7;
        int n = nums1.size();
        ll sum = 0;
        set<ll> setting;
        for(int i = 0; i < n; ++i)
        {
            sum += abs(nums1[i] - nums2[i]);
            setting.insert(nums1[i]);
        }
        ll ans = sum;
        for(int i = 0; i < n; ++i)
        {
            // 用什么数字替换 nums[i]
            // 尽可能接近 nums2[i]
            auto it = setting.lower_bound(nums2[i]); // 大于等于 nums2[i] 的最小的
            if(it == setting.end())
            {
                // 全都小于 nums2[i]
                ll x = *(--it);
                ans = min(ans, sum - abs(nums1[i] - nums2[i]) + abs(x - nums2[i]));
            }
            else
            {
                ll x = *it;
                ans = min(ans, sum - abs(nums1[i] - nums2[i]) + abs(x - nums2[i]));
                if(it != setting.begin())
                {
                    ll y = *(--it);
                    ans = min(ans, sum - abs(nums1[i] - nums2[i]) + abs(y - nums2[i]));
                }
            }
        }
        return ans % MOD;
    }
};
