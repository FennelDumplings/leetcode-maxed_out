// prob397: Integer Replacement

/*
 * https://leetcode-cn.com/problems/integer-replacement/
 */

class Solution {
public:
    int integerReplacement(int n) {
        using ll = long long;
        ll iter = n;
        int cnt = 0; // 记变为 1 的次数
        while(iter > 1)
        {
            if(iter == 3)
                iter -= 1;
            else if((iter & 3) == 3)
                iter += 1;
            else if((iter & 1) == 1)
                iter -= 1;
            else
                iter >>= 1;
            ++cnt;
        }
        return cnt;
    }
};
