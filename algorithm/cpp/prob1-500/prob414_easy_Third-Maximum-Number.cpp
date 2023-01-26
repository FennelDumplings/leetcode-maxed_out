// prob414: Third Maximum Number

/*
 * Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).
 */

/*
 * Example 1:
 * Input: [3, 2, 1]
 * Output: 1
 * Explanation: The third maximum is 1.
 * Example 2:
 * Input: [1, 2]
 * Output: 2
 * Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
 * Example 3:
 * Input: [2, 2, 3, 1]
 * Output: 1
 * Explanation: Note that the third maximum here means the third maximum distinct number.
 * Both numbers with value 2 are both considered as second maximum.
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        if(nums.empty()) return INT_MIN;
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        bool flag = false;
        int cnt = 0;
        for(int num: nums)
        {
            if(num == INT_MIN) flag = true;
            if(num == max1 || num == max2 || num == max3)
                continue;
            ++cnt;
            if(num > max1)
            {
                max3 = max2;
                max2 = max1;
                max1 = num;
            }
            else if(num > max2)
            {
                max3 = max2;
                max2 = num;
            }
            else if(num > max3)
            {
                max3 = num;
            }
        }
        if(flag) ++cnt;
        if(cnt < 3)
            return max1;
        return max3;
    }
};
