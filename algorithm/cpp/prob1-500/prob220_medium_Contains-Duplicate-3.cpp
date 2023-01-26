// Prob220: Contains Duplicate III

/*
 * Given an array of integers, find out whether there are two distinct indices i and j in the array
 * such that the absolute difference between nums[i] and nums[j] is at most t
 * and the absolute difference between i and j is at most k.
 */

/*
 * Input: nums = [1,2,3,1], k = 3, t = 0
 * Output: true
 * Example 2:
 * Input: nums = [1,0,1,1], k = 1, t = 2
 * Output: true
 * Example 3:
 * Input: nums = [1,5,9,1,5,9], k = 2, t = 3
 * Output: false
 */

#include <unordered_set>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        if(n <= 1 || k <= 0 || t < 0) return false;
        multiset<int> setting = {};
        if(k + 1 >= n)
        {
            for(int i = 0; i < n; ++i)
            {
                if(_find(setting, nums[i], t))
                    return true;
                else
                    setting.insert(nums[i]);
            }
            return false;
        }
        else
        {
            for(int i = 0; i <= k; ++i)
            {
                if(_find(setting, nums[i], t))
                    return true;
                else
                    setting.insert(nums[i]);
            }
            for(int i = 1; i <= n - 1 - k; ++i)
            {
                setting.erase(setting.find(nums[i - 1]));
                if(_find(setting, nums[i + k], t))
                    return true;
                else
                    setting.insert(nums[i + k]);
            }
            return false;
        }
    }

private:
    bool _find(const multiset<int> &setting, int num, int t)
    {
        if(setting.empty()) return false;
        // 返回第一个大于等于 num 的迭代器
        auto iter = setting.lower_bound(num);
        using ll = long long;
        if(iter == setting.end())
        {
            // 没有比 num 大的
            --iter;
            return (ll(num) - *iter <= t);
        }
        if(iter == setting.begin())
        {
            // 没有比 num 小的
            return (*iter - ll(num) <= t);
        }
        return ((*iter - ll(num)) <= t || (ll(num) - *(--iter)) <= t);
    }
};
