// prob229: Majority Element

/*
 * Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
 * Note: The algorithm should run in linear time and in O(1) space.
 */

/*
 * Example 1:
 * Input: [3,2,3]
 * Output: [3]
 * Example 2:
 * Input: [1,1,1,3,3,2,2,2]
 * Output: [1,2]
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// topk 法
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        nth_element(nums.begin(), nums.begin() + n / 3, nums.end());
        nth_element(nums.begin(), nums.begin() + 2 * n / 3, nums.end());
        int cand1 = nums[n / 3];
        int cand2 = nums[2 * n / 3];
        int cnt1 = 0, cnt2 = 0;
        vector<int> result;
        for(int num: nums)
        {
            if(num == cand1) cnt1++;
            else if(num == cand2) cnt2++;
        }
        if(cnt1 > n / 3) result.push_back(cand1);
        if(cnt2 > n / 3) result.push_back(cand2);
        return result;
    }
};

// 摩尔投票
class Solution_2 {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        int cand1, cand2;
        int cnt1 = 0, cnt2 = 0;
        vector<int> result;
        for(int num: nums)
        {
            if(num == cand1)
            {
                cnt1++;
                continue;
            }
            if(num == cand2)
            {
                cnt2++;
                continue;
            }
            if(!cnt1)
            {
                cand1 = num;
                cnt1 = 1;
                continue;
            }
            if(!cnt2)
            {
                cand2 = num;
                cnt2 = 1;
                continue;
            }
            // 此时三个元素不同，且都有数量
            cnt1--, cnt2--;
        }
        cnt1 = cnt2 = 0;
        for(int num: nums)
        {
            if(num == cand1) cnt1++;
            else if(num == cand2) cnt2++;
        }
        if(cnt1 > n / 3) result.push_back(cand1);
        if(cnt2 > n / 3) result.push_back(cand2);
        return result;
    }
};

// 直接计数
class Solution_3 {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        unordered_map<int, int> mapping;
        vector<int> result;
        for(int num: nums)
        {
            if(mapping.find(num) == mapping.end())
                mapping[num] = 1;
            else
                ++mapping[num];
            if(mapping[num] > n / 3 && (result.empty() || result[0] != num))
                result.push_back(num);
            if((int)result.size() >= 2)
                return result;
        }
        return result;
    }
};
