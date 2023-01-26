// prob201: Bitwise AND of Numbers Range

/*
 * Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
 */

/*
 * Example 1:
 * Input: [5,7]
 * Output: 4
 * Example 2:
 * Input: [0,1]
 * Output: 0
 */

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int res = 0;
        for(int i = 0; (1ll << i) <= m; ++i)
            if(m >> i & 1) // 只有 m 为 1 的位， 结果里该为才可能是 1
            {
                if((m & ~((1 << i) - 1ll) + (1 << i)) > n) //
                    res += 1 << i;
            }
        return res;
    }
};
