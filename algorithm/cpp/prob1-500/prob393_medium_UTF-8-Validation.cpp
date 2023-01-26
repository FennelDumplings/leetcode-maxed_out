// prob393: UTF-8 Validation

/*
 * https://leetcode-cn.com/problems/utf-8-validation/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int n = data.size();
        dp = vector<int>(n);
        return solve(data, 0);
    }

private:
    vector<int> dp;

    bool solve(const vector<int>& data, int i)
    {
        int n = data.size();
        if(i == n)
            return true;
        if(dp[i] != 0)
            return dp[i] == 1;
        for(int l = 1; l <= 4; ++l)
        {
            if(l == 1)
            {
                if((data[i] >> 7 & 1) == 0)
                    if(solve(data, i + 1))
                    {
                        dp[i] = 1;
                        return true;
                    }
                continue;
            }
            // data[i..i+l-1]
            if(i + l > n)
                break;
            int mask1 = (1 << (l + 1)) - 1;
            int check1 = mask1 - 1;
            int mask2 = (1 << 2) - 1;
            int check2 = mask2 - 1;
            bool flag = true;
            if(((data[i] >> (8 - (l + 1)) & mask1) == check1))
            {
                for(int j = i + 1; j < i + l; ++j)
                {
                    if(((data[j] >> 6) & mask2) != check2)
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag && solve(data, i + l))
                {
                    dp[i] = 1;
                    return true;
                }
            }
        }
        dp[i] = -1;
        return false;
    }
};
