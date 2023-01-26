
#include <unordered_map>
#include <vector>

using namespace std;

class Solution_2 {
public:
    bool splitArray(vector<int>& nums) {
        int n = nums.size();
        if(n < 7)
            return false;
        unordered_map<int, vector<int>> right_sum; // mapping[x] = [i1, i2, ...]: [i..n-1]的和为 x, i=i1, i2, ...
        int sum = 0;
        for(int i = n - 1; i >= 6; --i)
        {
            sum += nums[i];
            right_sum[sum].push_back(i);
        }
        vector<int> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + nums[i - 1];
        int target_sum = 0;
        for(int i = 1; i <= n - 6; ++i)
        {
            target_sum += nums[i - 1];
            if(right_sum.count(target_sum) == 0)
                continue;
            for(int idx: right_sum[target_sum])
            {
                int k = idx - 1;
                if(i + 4 > k)
                    break;
                for(int j = i + 2; j <= k - 2; ++j)
                {
                    if(sums[j] - sums[i + 1] == target_sum && sums[k] - sums[j + 1] == target_sum)
                        return true;
                }
            }
        }
        return false;
    }
};

#include <unordered_set>

class Solution {
public:
    bool splitArray(vector<int>& nums) {
        int n = nums.size();
        if(n < 7)
            return false;
        vector<int> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + nums[i - 1];
        unordered_set<int> setting;
        for(int j = 3; j <= n - 4; ++j)
        {
            setting.clear();
            for(int i = 1; i <= j - 2; ++i)
            {
                if(sums[i] == sums[j] - sums[i + 1])
                    setting.insert(sums[i]);
            }
            for(int k = j + 2; k < n - 1; ++k)
            {
                int target_sums = sums[k] - sums[j + 1];
                if(target_sums == sums[n] - sums[k + 1] && setting.count(target_sums) > 0)
                    return true;
            }
        }
        return false;
    }
};
