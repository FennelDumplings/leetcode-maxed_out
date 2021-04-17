// prob1109: Corporate Flight Bookings

/*
 * https://leetcode-cn.com/problems/corporate-flight-bookings/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> nums(n + 1);
        vector<int> diff(n + 1); // diff[i] = nums[i + 1] - nums[i]
        for(vector<int> &record: bookings)
        {
            int i = record[0], j = record[1], k = record[2];
            diff[i - 1] += k;
            diff[j] -= k;
        }
        for(int i = 1; i <= n; ++i)
            nums[i] = nums[i - 1] + diff[i - 1];
        for(int i = 0; i < n; ++i)
            nums[i] = nums[i + 1];
        nums.pop_back();
        return nums;
    }
};
