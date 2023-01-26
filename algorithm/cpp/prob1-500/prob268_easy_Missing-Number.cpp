// prob268: Missing Number

/*
 * Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
 */

/*
 * Example 1:
 * Input: [3,0,1]
 * Output: 2
 * Input: [9,6,4,2,3,5,7,0,1]
 * Output: 8
 */

#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] == -1) continue;
            int j = nums[i];
            while(j != n && nums[j] != -1)
            {
                int tmp = nums[j];
                nums[j] = -1;
                j = tmp;
            }
        }
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] != -1)
                return i;
        }
        return n;
    }
};
