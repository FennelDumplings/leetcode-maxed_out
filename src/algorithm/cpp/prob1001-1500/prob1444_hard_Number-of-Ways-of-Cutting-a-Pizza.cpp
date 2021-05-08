// prob1443: Number of Ways of Cutting a Pizza

/*
 * Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the pizza into k pieces using k-1 cuts. 
 * For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces. If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. Give the last piece of pizza to the last person.
 * Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.
 */

/*
 * Example 1:
 * Input: pizza = ["A..","AAA","..."], k = 3
 * Output: 3
 * Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.
 * Example 2:
 * Input: pizza = ["A..","AA.","..."], k = 3
 * Output: 1
 * Example 3:
 * Input: pizza = ["A..","A..","..."], k = 1
 * Output: 1
 */

/*
 * Constraints:
 * 1 <= rows, cols <= 50
 * rows == pizza.length
 * cols == pizza[i].length
 * 1 <= k <= 10
 * pizza consists of characters 'A' and '.' only.
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    // 结果有一步除以 2，每一步推导都取模有点麻烦
    // 直接在 dp 数组中用 ll
    // 最后再取 MOD
    int ways(vector<string>& pizza, int k) {
        int rows = pizza.size(), cols = pizza[0].size();
        vector<vector<int> > next_row(rows, vector<int>(cols, rows));
        vector<vector<int> > next_col(rows, vector<int>(cols, cols));
        if(pizza[rows - 1][cols - 1] == 'A')
        {
            next_col[rows - 1][cols - 1] = cols - 1;
            next_row[rows - 1][cols - 1] = rows - 1;
        }
        for(int i = rows - 1; i >= 0; --i)
        {
            for(int j = cols - 1; j >= 0; --j)
            {
                if(i == rows - 1 && j == cols - 1)
                    continue;
                if(pizza[i][j] == 'A')
                {
                    next_col[i][j] = j;
                    next_row[i][j] = i;
                }
                else
                {
                    if(i < rows - 1)
                    {
                        next_row[i][j] = min(next_row[i][j], next_row[i + 1][j]);
                        next_col[i][j] = min(next_col[i][j], next_col[i + 1][j]);
                    }
                    if(j < cols - 1)
                    {
                        next_row[i][j] = min(next_row[i][j], next_row[i][j + 1]);
                        next_col[i][j] = min(next_col[i][j], next_col[i][j + 1]);
                    }
                }
            }
        }

        vector<vector<vector<ll>>> dp(rows + 1, vector<vector<ll>>(cols + 1, vector<ll>(k + 1, -1)));
        solve(0, 0, k, pizza, dp, next_row, next_col);
        return (dp[0][0][k] / 2) % MOD;
    }

private:
    const int MOD = 1e9 + 7;
    using ll = long long;

    void solve(int i, int j, int k, const vector<string>& pizza, vector<vector<vector<ll>>>& dp,
            const vector<vector<int> >& next_row, const vector<vector<int> >& next_col)
    {
        if(dp[i][j][k] != -1)
            return;

        int rows = pizza.size(), cols = pizza[0].size();
        if(i >= rows || j >= cols)
        {
            if(k > 0)
                dp[i][j][k] = 0;
            else if(k == 0)
                dp[i][j][k] = 1;
            return;
        }

        if(i < rows && j < cols && k < 1)
        {
            dp[i][j][k] = 0;
            return;
        }

        // i < rows, j < cols, k >= 1
        dp[i][j][k] = 0;
        for(int x = next_row[i][j] + 1; x <= rows; ++x)
        {
            solve(x, j, k - 1, pizza, dp, next_row, next_col);
            dp[i][j][k] += dp[x][j][k - 1];
        }
        for(int y = next_col[i][j] + 1; y <= cols; ++y)
        {
            solve(i, y, k - 1, pizza, dp, next_row, next_col);
            dp[i][j][k] += dp[i][y][k - 1];
        }
    }
};

// 二维前缀和维护
class Solution_2 {
public:
    int ways(vector<string>& pizza, int k) {
        int rows = pizza.size(), cols = pizza[0].size();
        vector<vector<int> > sums(rows + 1, vector<int>(cols + 1, 0));
        for(int i = 1; i <= rows; ++i)
            for(int j = 1; j <= cols; ++j)
            {
                sums[i][j] = sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1];
                if(pizza[i - 1][j - 1] == 'A')
                    sums[i][j] += 1;
            }
        vector<vector<vector<ll>>> dp(rows, vector<vector<ll>>(cols, vector<ll>(k + 1, -1)));
        solve(0, 0, k, sums, dp);
        return dp[0][0][k] % MOD;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;

    void solve(int i, int j, int k, const vector<vector<int> >& sums, vector<vector<vector<ll>>>& dp)
    {
        if(dp[i][j][k] != -1)
            return;

        int rows = sums.size() - 1, cols = sums[0].size() - 1;
        if(k == 1)
        {
            dp[i][j][k] = 1;
            return;
        }

        // i < rows, j < cols, k > 1
        dp[i][j][k] = 0;
        for(int x = i; x < rows - 1; ++x)
        {
            if(query(i, j, x, cols - 1, sums) > 0 && query(x + 1, j, rows - 1, cols - 1, sums) > 0)
            {
                solve(x + 1, j, k - 1, sums, dp);
                // dp[i][j][k] = (dp[i][j][k] + dp[x + 1][j][k - 1]) % MOD;
                dp[i][j][k] += dp[x + 1][j][k - 1];
            }
        }
        for(int y = j; y < cols; ++y)
        {
            if(query(i, j, rows - 1, y, sums) > 0 && query(i, y + 1, rows - 1, cols - 1, sums) > 0)
            {
                solve(i, y + 1, k - 1, sums, dp);
                // dp[i][j][k] = (dp[i][j][k] + dp[i][y + 1][k - 1]) % MOD;
                dp[i][j][k] += dp[i][y + 1][k - 1];
            }
        }
    }

    int query(int row1, int col1, int row2, int col2, const vector<vector<int> >& sums) {
        if(sums.empty()) return -1;
        // row1 <= row2, col1 <= col2
        return sums[row2 + 1][col2 + 1] - sums[row2 + 1][col1]
            - sums[row1][col2 + 1] + sums[row1][col1];
    }
};

