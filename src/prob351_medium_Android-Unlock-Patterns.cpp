// prob351: Android Unlock Patterns

/*
 * Given an Android 3x3 key lock screen and two integers m and n, where 1 ≤ m ≤ n ≤ 9, count the total number of unlock patterns of the Android lock screen, which consist of minimum of m keys and maximum n keys.
 * Rules for a valid pattern:
 * Each pattern must connect at least m keys and at most n keys.
 * All the keys must be distinct.
 * If the line connecting two consecutive keys in the pattern passes through any other keys, the other keys must have previously selected in the pattern. No jumps through non selected key is allowed.
 * The order of keys used matters.
 * Explanation:
 * | 1 | 2 | 3 |
 * | 4 | 5 | 6 |
 * | 7 | 8 | 9 |
 * Invalid move: 4 - 1 - 3 - 6
 * Line 1 - 3 passes through key 2 which had not been selected in the pattern.
 * Invalid move: 4 - 1 - 9 - 2
 * Line 1 - 9 passes through key 5 which had not been selected in the pattern.
 * Valid move: 2 - 4 - 1 - 3 - 6
 * Line 1 - 3 is valid because it passes through key 2, which had been selected in the pattern
 * Valid move: 6 - 5 - 4 - 1 - 9 - 2
 * Line 1 - 9 is valid because it passes through key 5, which had been selected in the pattern.
 */

/*
 * Example:
 * Input: m = 1, n = 1
 * Output: 9
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numberOfPatterns(int m, int n) {
        // m <= k <= n
        // dp[state][i] 当前已经选 state, 当前在 i
        // dp[state][0~9]
        vector<vector<int> > dp((1 << 9) + 1, vector<int>(10, -1));
        vector<int> cnt(10, 0);
        for(int i = 1; i <= 9; ++i)
        {
            dp[(1 << (i - 1))][i] = 1;
        }
        for(int state = 1; state < (1 << 9) - 1; ++state)
        {
            for(int j = 1; j <= 9; ++j)
            {
                dfs(state, j, cnt, dp);
            }
        }

        int result = 0;
        for(int k = m; k <= n; ++k)
            result += cnt[k];
        return result;
    }

private:
    void dfs(int state, int j, vector<int>& cnt, vector<vector<int> >& dp)
    {
        // j 一定不在 state
        if(dp[state | (1 << (j - 1))][j] != -1)
            return;

        dp[state | (1 << (j - 1))][j] = 0;
        int k = hammingWeight(state);
        int cur_cnt = 0;
        for(int i = 1; i <= 9; ++i)
        {
            if(!(state & (1 << (i - 1)))) continue; // 选在 state 里的
            if(!_check(state, i, j)) continue;
            dfs((state & (~(1 << (i - 1)))), i, cnt, dp);
            dp[state|(1 << (j - 1))][j] += dp[state][i];
            cur_cnt += dp[state][i];
        }
        cnt[k] += cur_cnt;
    }

    // lc191 1 的个数
    int hammingWeight(int n) {
        int result = 0;
        while(n)
        {
            ++result;
            n &= (n - 1);
        }
        return result;
    }

    bool _check(int state, int i, int j)
    {
        if(i == 1 && j == 3) return (state & (1 << 1));
        if(i == 3 && j == 1) return (state & (1 << 1));
        if(i == 1 && j == 7) return (state & (1 << 3));
        if(i == 7 && j == 1) return (state & (1 << 3));
        if(i == 3 && j == 9) return (state & (1 << 5));
        if(i == 9 && j == 3) return (state & (1 << 5));
        if(i == 7 && j == 9) return (state & (1 << 7));
        if(i == 9 && j == 7) return (state & (1 << 7));
        if(i == 2 && j == 8) return (state & (1 << 4));
        if(i == 8 && j == 2) return (state & (1 << 4));
        if(i == 4 && j == 6) return (state & (1 << 4));
        if(i == 6 && j == 4) return (state & (1 << 4));
        if(i == 1 && j == 9) return (state & (1 << 4));
        if(i == 9 && j == 1) return (state & (1 << 4));
        if(i == 3 && j == 7) return (state & (1 << 4));
        if(i == 7 && j == 3) return (state & (1 << 4));
        return true;
    }
};

// DFS+剪枝
class Solution_2 {
public:
    int numberOfPatterns(int m, int n) {
        int result = 0;
        int state = 0;
        for(int i = 1; i <= 9; ++i)
            dfs((state | (1 << (i - 1))), i, result, n, m, 1);
        return result;
    }

private:
    void dfs(int state, int cur, int& result, int n, int m, int num)
    {
        if(num > n)
            return;
        if(num >= m)
            ++result;
        for(int i = 1; i <= 9; ++i)
        {
            if(state & (1 << (i - 1)))
                continue;
            if(!_check(state, cur, i))
                continue;
            dfs((state | (1 << (i - 1))), i, result, n, m, num + 1);
        }
    }

    bool _check(int state, int i, int j)
    {
        if(i == 1 && j == 3) return (state & (1 << 1));
        if(i == 3 && j == 1) return (state & (1 << 1));
        if(i == 1 && j == 7) return (state & (1 << 3));
        if(i == 7 && j == 1) return (state & (1 << 3));
        if(i == 3 && j == 9) return (state & (1 << 5));
        if(i == 9 && j == 3) return (state & (1 << 5));
        if(i == 7 && j == 9) return (state & (1 << 7));
        if(i == 9 && j == 7) return (state & (1 << 7));
        if(i == 2 && j == 8) return (state & (1 << 4));
        if(i == 8 && j == 2) return (state & (1 << 4));
        if(i == 4 && j == 6) return (state & (1 << 4));
        if(i == 6 && j == 4) return (state & (1 << 4));
        if(i == 1 && j == 9) return (state & (1 << 4));
        if(i == 9 && j == 1) return (state & (1 << 4));
        if(i == 3 && j == 7) return (state & (1 << 4));
        if(i == 7 && j == 3) return (state & (1 << 4));
        return true;
    }
};
