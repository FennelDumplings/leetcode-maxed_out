// interview53-1: 在排序数组中查找数字 I

/*
 * https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto result = equal_range(nums.begin(), nums.end(), target);
        return result.second - result.first;
    }
};

class Solution_2 {
public:
    int search(vector<int>& nums, int target) {
        int idx = get_idx(nums, target);
        if(idx == -1) return 0;
        int n = nums.size();
        int left = idx, right = idx;
        while(left >= 0 && nums[left] == target)
            --left;
        while(right < n && nums[right] == target)
            ++right;
        return right - left - 1;
    }

private:
    int get_idx(const vector<int>& nums, int target)
    {
        // 若不存在，返回 -1
        int n = nums.size();
        int left = 0, right = n - 1;
        while(left <= right)
        {
            int mid = (left + right) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }
};
