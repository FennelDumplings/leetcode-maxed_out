// prob645: Set Mismatch

/*
 * https://leetcode-cn.com/problems/set-mismatch/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        // 1...n
        using ll = long long;
        int n = nums.size();
        ll S1 = 0, S2 = 0;
        for(int i: nums)
        {
            S1 += i;
            S2 += i * i;
        }
        int a = S1 - (ll)n * (n + 1) / 2;
        int b = S2 - (ll)n * (n + 1) * (2 * n + 1) / 6;
        int x = (a + b / a) / 2;
        int y = x - a;
        return {x, y};
    }
};




