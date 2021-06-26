// prob228: Summary Ranges

/*
 * Given a sorted integer array without duplicates, return the summary of its ranges.
 */

/*
 * Example 1:
 * Input:  [0,1,2,4,5,7]
 * Output: ["0->2","4->5","7"]
 * Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.
 * Example 2:
 * Input:  [0,2,3,4,6,8,9]
 * Output: ["0","2->4","6","8->9"]
 * Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if(nums.empty()) return vector<string>();
        int n = nums.size();
        int left = 0;
        vector<string> result;
        while(left < n)
        {
            int right = left + 1;
            while(right < n && nums[right] == nums[right - 1] + 1)
                ++right;
            string item = to_string(nums[left]);
            if(left + 1 < right)
                item += "->" + to_string(nums[right - 1]);
            result.push_back(item);
            left = right;
        }
        return result;
    }
};
