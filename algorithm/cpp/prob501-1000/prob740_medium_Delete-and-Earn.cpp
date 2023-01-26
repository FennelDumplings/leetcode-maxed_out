// prob740: Delete and Earn

/*
 * Given an array nums of integers, you can perform operations on the array.
 * In each operation, you pick any nums[i] and delete it to earn nums[i] points. After, you must delete
 * every element equal to nums[i] - 1 or nums[i] + 1.
 * You start with 0 points. Return the maximum number of points you can earn by applying such operations.
 */

/*
 * Example 1:
 * Input: nums = [3, 4, 2]
 * Output: 6
 * Explanation:
 * Delete 4 to earn 4 points, consequently 3 is also deleted.
 * Then, delete 2 to earn 2 points. 6 total points are earned.
 * Example 2:
 * Input: nums = [2, 2, 3, 3, 3, 4]
 * Output: 9
 * Explanation:
 * Delete 3 to earn 3 points, deleting both 2's and the 4.
 * Then, delete 3 again to earn 3 points, and 3 again to earn 3 points.
 * 9 total points are earned.
 */

/*
 * Note:
 * The length of nums is at most 20000.
 * Each element nums[i] is an integer in the range [1, 10000].
 */

#include <vector>

using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        const int N = 10001;
        vector<int> vals(N, 0);
        for(int num: nums) ++vals[num];
        for(int i = 1; i < N; ++i)
            vals[i] *= i;
        vector<int> dp(N, 0);
        dp[1] = vals[1];
        for(int i = 2; i < N; ++i)
            dp[i] = max(vals[i] + dp[i - 2], dp[i - 1]);
        return dp[N - 1];
     }
};
