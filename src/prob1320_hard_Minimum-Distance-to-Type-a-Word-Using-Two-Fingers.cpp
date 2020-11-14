// prob1320: Minimum Distance to Type a Word Using Two Fingers

/*
 * https://leetcode-cn.com/problems/minimum-distance-to-type-a-word-using-two-fingers/
 */

#include <string>
#include <climits>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:
    int minimumDistance(string word) {
        for(int i = 1; i <= 26; ++i)
            for(int j = 1; j <= 26; ++j)
                D[i][j] = INT_MAX / 2;
        for(int i = 1; i <= 26; ++i)
        {
            D[i][i] = 0;
            D[0][i] = 0;
            if((i - 1) % 6 < 5 && i + 1 <= 26)
            {
                D[i][i + 1] = 1;
                D[i + 1][i] = 1;
            }
            if(i + 6 <= 26)
            {
                D[i][i + 6] = 1;
                D[i + 6][i] = 1;
            }
        }
        for(int k = 1; k <= 26; ++k)
            for(int i = 1; i <= 26; ++i)
                for(int j = 1; j <= 26; ++j)
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

        int n = word.size();
        // dp[x][y][i] := 当前两指在 x, y，走 [i..n-1] 的最短路径
        for(int x = 0; x <= 26; ++x)
            for(int y = 0; y <= 26; ++y)
                dp[x][y] = vector<int>(n, -1);

        return solve(0, 0, 0, word);
    };

private:
    int D[27][27];
    vector<int> dp[27][27];

    int solve(int x, int y, int i, const string& s)
    {
        int n = s.size();
        if(i == n)
            return 0;
        // dp[x][y][i] := 当前两指在 x, y，走 [i..n-1] 的最短路径
        if(dp[x][y][i] != -1)
            return dp[x][y][i];

        int nxt = s[i] - 'A' + 1;
        dp[x][y][i] = min(D[x][nxt] + solve(nxt, y, i + 1, s), D[y][nxt] + solve(x, nxt, i + 1, s));
        return dp[x][y][i];
    }
};
