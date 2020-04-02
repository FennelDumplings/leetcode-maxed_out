// prob453: Minimum Moves to Equal Array Elements

/*
 * Given a non-empty integer array of size n, find the minimum number of moves required to make all array elements equal, where a move is incrementing n - 1 elements by 1.
 */

/*
 * Example:
 * Input:
 * [1,2,3]
 * Output:
 * 3
 * Explanation:
 * Only three moves are needed (remember each move increments two elements):
 * [1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int mx = nums[0]; // 当前最小值
        int result = 0;
        for(int i = 1; i < n; ++i)
        {
            if(nums[i] >= mx)
                result += nums[i] - mx;
            else
            {
                result += (mx - nums[i]) * i;
                mx = nums[i];
            }
        }
        return result;
    }
};
