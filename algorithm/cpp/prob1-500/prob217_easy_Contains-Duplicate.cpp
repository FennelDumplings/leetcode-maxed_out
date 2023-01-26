// Prob217: Contains Duplicate

/*
 * Given an array of integers, find if the array contains any duplicates.
 * Your function should return true if any value appears at least twice in the array,
 * and it should return false if every element is distinct.
 */

/*
 * Example 1:
 *
 * Input: [1,2,3,1]
 * Output: true
 * Example 2:
 *
 * Input: [1,2,3,4]
 * Output: false
 * Example 3:
 *
 * Input: [1,1,1,3,3,4,3,2,4,2]
 * Output: true
 */

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        if(nums.size() <= 1) return false;
        unordered_set<int> setting;
        setting.insert(nums[0]);
        for(size_t i = 1; i < nums.size(); ++i)
        {
            if(setting.find(nums[i]) != setting.end())
                return true;
            else
                setting.insert(nums[i]);
        }
        return false;
    }
};
