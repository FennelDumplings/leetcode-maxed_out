// prob16: 3Sum Closest

/*
 * Given an array nums of n integers and an integer target,
 * find three integers in nums such that the sum is closest to target.
 * Return the sum of the three integers.
 * You may assume that each input would have exactly one solution.
 */

/*
 * in nums such that the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
 * Example:
 * Given array nums = [-1, 2, 1, -4], and target = 1.
 * The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        // 已知有且只有一组答案，所以 n >= 3
        sort(nums.begin(), nums.end());
        int result = nums[0] + nums[1] + nums[2] - target;
        for(int i = 0; i < n - 2; i++)
        {
            int gap = target - nums[i];
            int left = i + 1, right = n - 1;
            int d = 0;
            while(left < right)
            {
                d = nums[left] + nums[right] - gap;
                if(d > 0)
                    --right;
                else if(d < 0)
                    ++left;
                else
                    return nums[i] + nums[left] + nums[right];
                result = compare(result, d);
            }
        }
        return result + target;
    }

private:
    int compare(int gap1, int gap2)
    {
        if(abs(gap1) > abs(gap2))
            return gap2;
        else
            return gap1;
    }
};
