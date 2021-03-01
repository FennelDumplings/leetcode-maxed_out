// prob754: Reach a Number

/*
 * https://leetcode-cn.com/problems/reach-a-number/
 */

class Solution {
public:
    int reachNumber(int target) {
        if(target < 0)
            return reachNumber(-target);
        using ll = long long;
        int i = 1;
        ll S = 0;
        while(S < target)
        {
            S += i;
            ++i;
        }
        int K = i - 1;
        if(S == target || (S - target) % 2 == 0)
            return K;
        ll S1 = S + K + 1;
        if((S1 - S) % 2 == 1)
            return K + 1;
        return K + 2;
    }
};
