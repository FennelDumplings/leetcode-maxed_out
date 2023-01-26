// Prob219: Contains Duplicate 2

/*
 * Given an array of integers and an integer k,
 * find out whether there are two distinct indices i and j in the array
 * such that nums[i] = nums[j]
 * and the absolute difference between i and j is at most k.
 */

/*
 * Example 1:
 * Input: nums = [1,2,3,1], k = 3
 * Output: true
 * Example 2:
 * Input: nums = [1,0,1,1], k = 1
 * Output: true
 * Example 3:
 * Input: nums = [1,2,3,1,2,3], k = 2
 * Output: false
 */

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        if(n <= 1 || k <= 0) return false;
        unordered_set<int> setting = {};
        if(k + 1 >= n)
        {
            for(int i = 0; i < n; ++i)
            {
                if(setting.find(nums[i]) != setting.end())
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
                if(setting.find(nums[i]) != setting.end())
                    return true;
                else
                    setting.insert(nums[i]);
            }
            for(int i = 1; i <= n - 1 - k; ++i)
            {
                setting.erase(setting.find(nums[i - 1]));
                if(setting.find(nums[i + k]) != setting.end())
                    return true;
                else
                    setting.insert(nums[i + k]);
            }
            return false;
        }
    }
};
