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

class Solution {
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
