// Prob1: Two Sum

/*Description
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
*/

/*
 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1]
 */

#include <vector>
#include <unordered_map>
#include <iostream>
#include <iterator>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        //因为保证只有一个结果，所以插入哈希表中的重复数字不可能是结果，因此可用map代替multimap
        //边插入边查找, 可以少遍历一次
        unordered_map<int, int> mapping;
        vector<int> result(2, 0);

        for(size_t i = 0; i < nums.size(); ++i)
        {
            int gap = target - nums[i];
            unordered_multimap<int, int>::iterator pos = mapping.find(gap);
            if(pos != mapping.end())
            {
                result[0] = i;
                result[1] = pos -> second;
                break;
            }
            mapping[nums[i]] = i;
        }
        return result;
    }
};


int main()
{
    int n;
    cout << "input the length of array: " << endl;
    cin >> n;
    vector<int> a(n, 0);
    cout << "input array: " << endl;
    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    int tar;
    cout << "input target: " << endl;
    cin >> tar;
    vector<int> result;
    Solution solution;
    result = solution.twoSum(a, tar);
    cout << result[0] << "  " << result[1] << endl;
}

// Tags
// Hash Table
// Array

/*
 * Similar Problem
 * 3Sum -- Medium
 * 4Sum -- Medium
 * Two Sum II - Input array is sorted -- Easy
 * Two Sum III - Data structure design -- Easy
 * Subarray Sum Equals K -- Medium
 * Two Sum IV - Input is a BST -- Easy
 */
