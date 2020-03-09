// prob442: Find All Duplicates in an Array

/*
 * Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
 * Find all the elements that appear twice in this array.
 * Could you do it without extra space and in O(n) runtime?
 */

/*
 * Example:
 * Input:
 * [4,3,2,7,8,2,3,1]
 * Output:
 * [2,3]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n == 1) return vector<int>();
        for(int i = 0; i < n; ++i)
        {
            // i -> nums[i] - 1索引位置计数为-1或-2
            if(nums[i] < 0) continue;
            int j = nums[i] - 1;
            nums[i] = 0;
            while(nums[j] > 0)
            {
                int tmp = nums[j] - 1;
                nums[j] = -1;
                j = tmp;
            }
            if(nums[j] <= 0)
                --nums[j];
        }
        vector<int> result;
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] == -2)
                result.push_back(i + 1);
        }
        return result;
    }
};
