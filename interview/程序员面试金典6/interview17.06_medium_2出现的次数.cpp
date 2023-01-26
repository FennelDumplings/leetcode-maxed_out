// interview17.06: 2出现的次数

/*
 * https://leetcode-cn.com/problems/number-of-2s-in-range-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numberOf2sInRange(int n) {
        if(n == 0) return 0;
        return solve(n);
    }

private:
    int solve(int n)
    {
        vector<int> digits;
        while(n)
        {
            digits.push_back(n % 10);
            n /= 10;
        }

        int m = digits.size();
        vector<vector<int> > dp(m, vector<int>(m, -1));
        int ans = getdp(m - 1, 1, 1, 0, digits, dp);
        return ans;
    }

    int getdp(int pos, int lim, int zero, int cnt, const vector<int>& digits, vector<vector<int>>& dp)
    {
        if(pos == -1) return cnt;
        if(!lim && !zero && dp[pos][cnt] != -1)
            return dp[pos][cnt];
        int ans = 0;
        int up = lim ? digits[pos] : 9;
        if(zero)
            ans += getdp(pos - 1, 0, 1, cnt, digits, dp);
        for(int i = 0; i <= 9; ++i)
        {
            if(i > up)
                break;
            if(zero && i == 0)
                continue;
            ans += getdp(pos - 1, lim && i == up, 0, cnt + (i == 2), digits, dp);
        }
        if(!lim && !zero)
            dp[pos][cnt] = ans;
        return ans;
    }
};
