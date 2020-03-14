// prob462: Minimum Moves to Equal Array Elements

/*
 * Given a non-empty integer array, find the minimum number of moves required to make all array elements equal,
 * where a move is incrementing a selected element by 1 or decrementing a selected element by 1.
 * You may assume the array's length is at most 10,000.
 */

/*
 * Example:
 * Input:
 * [1,2,3]
 * Output:
 * 2
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
        int m = nums[n / 2];
        int result = 0;
        for(int num: nums)
            result += abs(num - m);
        return result;
    }
};
