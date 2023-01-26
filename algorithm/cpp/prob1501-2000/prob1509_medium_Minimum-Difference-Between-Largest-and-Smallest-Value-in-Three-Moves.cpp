// prob1509: Minimum Difference Between Largest and Smallest Value in Three Moves

/*
 * https://leetcode-cn.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/
 */

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        if(n <= 4)
            return 0;
        nth_element(nums.begin(), nums.begin() + 4, nums.end());
        vector<int> minxs(nums.begin(), nums.begin() + 4);
        nth_element(nums.begin(), nums.end() - 4, nums.end());
        vector<int> maxxs(nums.end() - 4, nums.end());
        sort(maxxs.begin(), maxxs.end());
        sort(minxs.begin(), minxs.end());
        vector<int> cand{
            maxxs[0] - minxs[0],
            maxxs[1] - minxs[1],
            maxxs[2] - minxs[2],
            maxxs[3] - minxs[3]
        };
        return *min_element(cand.begin(), cand.end());
    }
};
