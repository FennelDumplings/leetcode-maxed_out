// interview14-2: 剪绳子 II

/*
 * https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/
 */

class Solution {
public:
    int cuttingRope(int n) {
        if(n == 2) return 1;
        if(n == 3) return 2;
        if(n == 4) return 4;
        using ll = long long;
        const int MOD = 1e9 + 7;
        int ans = 1;
        while(n > 4)
        {
            ans = ((ll)ans * 3) % MOD;
            n -= 3;
        }
        if(n == 2)
            ans = ((ll)ans * 2) % MOD;
        else if(n == 3)
            ans = ((ll)ans * 3) % MOD;
        else
            ans = ((ll)ans * 4) % MOD;
        return ans;
    }
};
