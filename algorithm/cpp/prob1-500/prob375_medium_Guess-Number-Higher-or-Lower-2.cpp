// prob375: Guess Number Higher or Lower II

/*
 * We are playing the Guess Game. The game is as follows:
 * I pick a number from 1 to n. You have to guess which number I picked.
 * Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.
 * However, when you guess a particular number x, and you guess wrong, you pay $x.
 * You win the game when you guess the number I picked.
 * Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.
 */

/*
 * Example:
 * n = 10, I pick 8.
 * First round:  You guess 5, I tell you that it's higher. You pay $5.
 * Second round: You guess 7, I tell you that it's higher. You pay $7.
 * Third round:  You guess 9, I tell you that it's lower. You pay $9.
 * Game over. 8 is the number I picked.
 * You end up paying $5 + $7 + $9 = $21.
 */

#include <vector>
#include <climits>

using namespace std;

// 博弈型dp
// dp[i][j] = [i, j] 中包赢的最小费用
// dp[i][j] = min(dp[i][j], max(dp[k+1][j], dp[i][k-1]) + k)
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int> > dp(n + 1, vector<int>(n + 1, INT_MAX));
        for(int i = 1; i <= n; ++i)
            dp[i][i] = 0;
        for(int j = 2; j <= n; ++j)
            for(int i = j - 1; i >= 1; --i)
            {
                dp[i][j] = min(dp[i + 1][j] + i, dp[i][j - 1] + j);
                for(int k = i + 1; k <= j - 1; ++k)
                    dp[i][j] = min(dp[i][j], max(dp[k + 1][j], dp[i][k - 1]) + k);
            }
        return dp[1][n];
    }
};

// 有点像矩阵链乘法
// 相似的题目有 887鸡蛋掉落 312戳气球 132分割回文串
