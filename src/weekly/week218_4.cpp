#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = INT_MAX / 2;
        int sum = 0;
        dfs(nums, k, (1 << n) - 1, sum, ans);
        if(ans == INT_MAX / 2)
            return -1;
        return ans;
    }

private:
    void dfs(const vector<int>& nums, const int k, int remain, int& sum, int& ans)
    {
        if(remain == 0)
        {
            ans = min(ans, sum);
            return;
        }
        int n = nums.size();
        int C = n / k;
        // remain 中选择长为 C 的子集
        for(int subset = (remain - 1) & remain; subset != remain; subset = (subset - 1) & remain)
        {
            // 长度限制
            if(ones(subset) != C)
                continue;
            // 重复限制
            int setting = 0;
            bool flag = true;
            for(int i = 0; i < n; ++i)
            {
                if(subset >> i & 1)
                {
                    if(setting >> nums[i] & 1)
                    {
                        flag = false;
                        break;
                    }
                    setting |= 1 << nums[i];
                }
            }
            if(!flag)
                continue;
            // 最大值最小值
            int maxx = INT_MIN / 2;
            int minx = INT_MAX / 2;
            for(int i = 0; i < n; ++i)
            {
                if(subset >> i & 1)
                {
                    minx = min(minx, nums[i]);
                    maxx = max(maxx, nums[i]);
                }
            }
            int val = maxx - minx;
            sum += val;
            dfs(nums, k, remain & subset, sum, ans);
            sum -= val;
        }
    }

    int ones(int x)
    {
        int cnt = 0;
        while(x)
        {
            x = x & (x - 1);
            ++cnt;
        }
        return cnt;
    }
};
