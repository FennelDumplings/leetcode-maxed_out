// prob169: Majority Element

/*
 * Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
 * You may assume that the array is non-empty and the majority element always exist in the array.
 */

/*
 * Example 1:
 * Input: [3,2,3]
 * Output: 3
 * Example 2:
 * Input: [2,2,1,1,1,2,2]
 * Output: 2
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution_4 {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> mapping;
        int result = 0;
        for(int num: nums)
        {
            if(mapping.find(num) == mapping.end())
                mapping[num] = 1;
            else
                ++mapping[num];
            result = max(result, mapping[num]);
            if(result > n / 2)
                return num;
        }
        return -1;
    }
};

// 抽象成快速选择问题
class Solution_2 {
public:
    int majorityElement(vector<int>& nums) {
        nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
        return nums[nums.size() / 2];
    }
};

// 摩尔投票
class Solution_3 {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int v, cnt = 0;
        for(int num: nums)
        {
            if(!cnt)
            {
                v = num;
                cnt = 1;
                continue;
            }
            if(num == v)
                ++cnt;
            else
                --cnt;
        }
        return v;
    }
};


class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        return solve(nums, 0, n - 1);
    }

private:
    int solve(const vector<int>& nums, int l, int r)
    {
        if(l == r)
            return nums[l];
        int mid = (l + r) / 2;
        int left = solve(nums, l, mid);
        int right = solve(nums, mid + 1, r);
        if(left == right)
            return left;
        int cnt_left = 0;
        int cnt_right = 0;
        for(int i = l; i <= r; ++i)
        {
            if(nums[i] == left)
                ++cnt_left;
            if(nums[i] == right)
                ++cnt_right;
        }
        if(cnt_left > cnt_right)
            return left;
        else
            return right;
    }
};
