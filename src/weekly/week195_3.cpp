
#include <vector>
#include <algorithm>

using namespace std;

using namespace std;

class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            int cur = nums[i];
            if(cur > target) break;
            // 以 cur 结尾, cur 是最大, 看最小
            // minx + cur <= target
            // minx <= target - cur = gap
            int gap = target - cur;
            // 大于 gap 的第一个值
            auto it = upper_bound(nums.begin(), nums.begin() + i, gap);
            int min_cand_len = it - nums.begin();
            int opt_len = i - min_cand_len;
            // (2^opt_len) * (1 + 2^1 + 2^2 + ... + 2^(min_cand_len - 1))
            if(min_cand_len == 0)
            {
                if(cur + cur <= target)
                    result = ((ll)result + 1) % MOD;
                continue;
            }
            if(min_cand_len == i)
            {
                int m = quickpower2(2, min_cand_len, MOD);
                result = (result + (ll)m) % MOD;
                if(cur + cur > target)
                    result = (result - 1 + MOD) % MOD;
                continue;
            }
            int m1 = quickpower2(2, opt_len, MOD);
            // int m2 = 0;
            // for(int l = 0; l < min_cand_len; ++l)
            // {
            //     m2 = ((ll)m2 + quickpower2(2, l, MOD)) % MOD;
            // }
            int m2 = ((quickpower2(2, min_cand_len, MOD)) - 1 + MOD) % MOD;
            int add = ((ll)m2 * m1) % MOD;
            result = ((ll)result + add) % MOD;
        }
        return result;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    int quickpower2(int a, int n, int m) // 处理不了n是负数
    {
        int ans = 1;
        while(n)
        {
            if(n & 1) ans = ((ll)ans * a) % m;
            a = (ll)a * a % m;
            n >>= 1;
        }
        return ans;
    }
};
