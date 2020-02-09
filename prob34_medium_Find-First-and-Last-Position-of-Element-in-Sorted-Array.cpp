// prob34: Find First and Last Position of Element in Sorted Array

/*
 * Given an array of integers nums sorted in ascending order,
 * find the starting and ending position of a given target value.
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * If the target is not found in the array, return [-1, -1].
 */

/*
 * Example 1:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 * Example 2:
 * Input: nums = [5,7,7,8,8,10], target = 6
 * Output: [-1,-1]
 */

#include <vector>
#include <algorithm>

using namespace std;

// 二分的 while 模板
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return vector<int>(2, -1);
        int n = nums.size();
        int left = 0, right = n;
        int mid = -1;
        int pos = -1; // 首次出现的位置
        while(left < right)
        {
            mid = left + (right - left) / 2;
            if(nums[mid] == target)
            {
                pos = mid;
                break;
            }
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        if(pos == -1) return vector<int>(2, -1);
        int lright = mid, rleft = mid + 1; // 左半段的右端; 右半段的左端
        while(left < lright)
        {
            // 循环结束的 lright 是结果的左端点
            int lmid = left + (lright - left) / 2;
            if(nums[lmid] == target)
                lright = lmid;
            else
                left = lmid + 1;
        }
        while(rleft < right)
        {
            // 循环结束的 right - 1 是结果的左端点
            int rmid = rleft + (right - rleft) / 2;
            if(nums[rmid] == target)
                rleft = rmid + 1;
            else
                right = rmid;
        }
        return vector<int>{lright, rleft - 1};
    }
};

// STL 写法
class Solution_STL {
public:
    vector<int> searchRange(vector<int>& nums, int target)
    {
        vector<int> result(2, -1);
        pair<vector<int>::iterator, vector<int>::iterator> range = equal_range(nums.begin(),nums.end(),target);
        if(range.first!=nums.end() && *(range.first)==target)
        {
            result[0] = distance(nums.begin(), range.first);
            result[1] = distance(nums.begin(), range.second-1);
        }
        return result;
    }
};
