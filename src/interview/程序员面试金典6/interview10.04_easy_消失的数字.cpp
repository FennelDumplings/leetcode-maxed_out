// interview17.04: 消失的数字

/*
 * https://leetcode-cn.com/problems/missing-number-lcci/
 */
I
#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int S = n * (n + 1) / 2;
        int sum = 0;
        for(int i: nums)
            sum += i;
        return S - sum;
    }
};
