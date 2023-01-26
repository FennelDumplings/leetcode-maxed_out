// prob1552: Minimum Operations to Make Array Equal

/*
 * https://leetcode-cn.com/problems/minimum-operations-to-make-array-equal/
 */


class Solution {
public:
    int minOperations(int n) {
        if(n & 1)
        {
            int mid = n / 2;
            int k = 2 * mid + 1;
            return k * (mid + 1) - (1 + k) * (mid + 1) / 2;
        }
        else
        {
            int mid = n / 2 - 1;
            int k = 2 * mid + 1;
            int ans = k * (mid + 1) - (1 + k) * (mid + 1) / 2;
            ans += mid + 1;
            return ans;
        }
    }
};
