// prob788: Rotated Digits

/*
 * https://leetcode-cn.com/problems/rotated-digits/
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int rotatedDigits(int N) {
        num_set = {2, 5, 6, 9};
        return solve(N) - 1;
    }

private:
    unordered_set<int> num_set;
    int solve(int n)
    {
        vector<int> digits;
        while(n)
        {
            digits.push_back(n % 10);
            n /= 10;
        }
        int m = digits.size();
        vector<vector<int>> dp(2, vector<int>(m, -1));
        int ans = getdp(m - 1, 1, 1, 0, digits, dp);
        return ans;
    }

    int getdp(int pos, int lim, int zero, int state, const vector<int>& digits, vector<vector<int>>& dp)
    {
        if(pos == -1) return state == 1;
        if(!zero && !lim && dp[state][pos] != -1)
            return dp[state][pos];
        int ans = 0;
        if(zero)
            ans = getdp(pos - 1, 0, 1, 0, digits, dp);
        int up = digits[pos];
        for(int i: {0, 1, 2, 5, 6, 8, 9})
        {
            if(lim && i > up) break;
            if(i == 0 && zero)
                continue;
            ans += getdp(pos - 1, lim && i == up, 0, state || num_set.count(i) == 0, digits, dp);
        }
        if(!zero && !lim)
            dp[state][pos] = ans;
        return ans;
    }
};
