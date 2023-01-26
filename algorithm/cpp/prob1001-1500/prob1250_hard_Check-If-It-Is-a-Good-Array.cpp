// prob1250: Check If It Is a Good Array

/*
 * https://leetcode-cn.com/problems/check-if-it-is-a-good-array/
 */

#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        if(nums.empty()) return false;
        int n = nums.size();
        if(n == 1) return abs(nums[0]) == 1;
        int all_gcd = gcd<int>(abs(nums[0]), abs(nums[1]));
        for(int i = 2; i < n;++i)
            all_gcd = gcd<int>(all_gcd, abs(nums[i]));
        return all_gcd == 1;
    }
};
