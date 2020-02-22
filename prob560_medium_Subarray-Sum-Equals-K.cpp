// prob560: Subarray Sum Equals K

/*
 * Given an array of integers and an integer k,
 * you need to find the total number of continuous subarrays whose sum equals to k.
 */

/*
 * Example 1:
 * Input:nums = [1,1,1], k = 2
 * Output: 2
 */

/*
 * Note:
 * The length of the array is in range [1, 20,000].
 * The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // 把所有前缀和保存到 unordered_map 中
        // 一遍 init 前缀和数组一遍把前缀和存入 map
        // 遍历的新的前缀和 S[i] 的时候，看有 map 没有元素为 S[i] - target
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<int> sums(n + 1, 0); // sums[0] = 0 是第一个前缀和
        unordered_map<int, int> sum_count;
        sum_count.insert(pair<int, int>(0, 1)); // 0 要初始化进去
        int result = 0;
        for(int i = 1; i < n + 1; ++i)
        {
            sums[i] = nums[i - 1] + sums[i - 1];
            if(sum_count.find(sums[i] - k) != sum_count.end())
                result += sum_count[sums[i] - k];
            if(sum_count.find(sums[i]) != sum_count.end())
                sum_count[sums[i]]++;
            else
                sum_count.insert(pair<int, int>(sums[i], 1));
        }
        return result;
    }
};

// 用 unordered_multiset
class Solution_2 {
public:
    int subarraySum(vector<int>& nums, int k) {
        // 把所有前缀和保存到 unordered_map 中
        // 一遍 init 前缀和数组一遍把前缀和存入 map
        // 遍历的新的前缀和 S[i] 的时候，看有 map 没有元素为 S[i] - target
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<int> sums(n + 1, 0); // sums[0] = 0 是第一个前缀和
        unordered_multiset<int> sum_count;
        sum_count.insert(0); // 0 要初始化进去
        int result = 0;
        for(int i = 1; i < n + 1; ++i)
        {
            sums[i] = nums[i - 1] + sums[i - 1];
            result += sum_count.count(sums[i] - k);
            sum_count.insert(sums[i]);
        }
        return result;
    }
};
