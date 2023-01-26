// prob1413: Minimum Value to Get Positive Step by Step Sum

/*
 * https://leetcode-cn.com/problems/minimum-value-to-get-positive-step-by-step-sum/
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minStartValue(vector<int>& nums) {
        int sum = 0;
        int minx = INT_MAX;
        for(int i: nums)
        {
            sum += i;
            minx = min(minx, sum);
        }
        return max(1 - minx, 1);
    }
};
