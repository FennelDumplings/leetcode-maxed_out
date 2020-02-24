// prob41: First Missing Positive

/*
 * Given an unsorted integer array, find the smallest missing positive integer.
 */

/*
 * Example 1:
 * Input: [1,2,0]
 * Output: 3
 * Example 2:
 * Input: [3,4,-1,1]
 * Output: 2
 * Example 3:
 * Input: [7,8,9,11,12]
 * Output: 1
 */

#include <vector>

using namespace std;

// vector 本身的索引范围可以覆盖取值范围的时候，该 vector 可以当哈希表使用
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if(nums.empty()) return 1;
        int n = nums.size();
        for(int i = 0; i < n; ++i)
        {
            int cur = nums[i];
            int j = i;
            while(!check(cur, j, n))
            {
                j = cur - 1;
                cur = nums[j];
                nums[j] = j + 1;
            }
        }
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] != i + 1)
                return i + 1;
        }
        return n + 1;
    }

private:
    bool check(int cur, int i, int n)
    {
        return (cur == i + 1 || cur <= 0 || cur > n);
    }
};
