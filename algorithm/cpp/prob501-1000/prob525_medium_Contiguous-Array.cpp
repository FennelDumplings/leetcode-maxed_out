// prob525: Contiguous Array

/*
 * Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.
 */

/*
 * Example 1:
 * Input: [0,1]
 * Output: 2
 * Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
 * Example 2:
 * Input: [0,1,0]
 * Output: 2
 * Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
 */

/*
 * Note: The length of the given binary array will not exceed 50,000.
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        unordered_map<int, int> mapping; // sum, i [0..i] 的前缀和
        mapping[0] = 0;
        int sum = 0;
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] == 0)
                --sum;
            else
                ++sum;
            int gap = -sum;
            if(mapping.count(gap))
                result = max(result, i + 1 - mapping[gap]);
            else
                mapping[gap] = i + 1;
        }
        return result;
    }
};
