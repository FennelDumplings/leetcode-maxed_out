// prob651: 4 Keys Keyboard

/*
 * https://leetcode-cn.com/problems/4-keys-keyboard/
 */

#include <vector>
#include <unordered_map>

using namespace std;

// 不带记忆化的递归
// N = 26， 1200ms
class Solution {
public:
    int maxA(int N) {
        return solve(0, N, 0);
    }

private:
    int solve(int i, int j, int k)
    {
        if(j == 0) return 0;
        int ans = 0;
        ans = 1 + solve(i + 1, j - 1, k);
        if(k > 0)
            ans = max(ans, k + solve(i + k, j - 1, k));
        if(j >= 3)
            ans = max(ans, i + solve(i + i, j - 3, i));
        return ans;
    }
};

// 记忆化
// N = 39, 1444ms
class Solution_2 {
public:
    int maxA(int N) {
        unordered_map<int, vector<int>> dp;
        return solve(0, 0, N, dp, N);
    }

private:
    int solve(int i, int j, int k, unordered_map<int, vector<int>>& dp, int N)
    {
        // 已有 i, 缓冲区内有 j, 剩余 k 步
        if(k == 0) return 0;
        int key = hash(i, j);
        if(dp.count(key) == 0)
        {
            dp[key] = vector<int>(max(4, N + 1), -1);
            dp[key][0] = 0;
        }
        if(dp[key][k] != -1)
            return dp[key][k];
        int ans = 1 + solve(i + 1, j, k - 1, dp, N);
        ans = max(ans, j + solve(i + j, j, k - 1, dp, N));
        if(k >= 3)
            ans = max(ans, i + solve(i + i, i, k - 3, dp, N));
        return dp[key][k] = ans;
    }

    int hash(int i, int j)
    {
        return i * 100 + j;
    }
};


// 记忆化
// vector 代替哈希表
// N = 39, 1444ms
class Solution_3 {
public:
    int maxA(int N) {
        vector<vector<int>> dp(M * 100 + 50 + 1, vector<int>(N));
        return solve(0, 0, N, dp, N);
    }

private:
    const int M = 50;

    int solve(int i, int j, int k, vector<vector<int>>& dp, int N)
    {
        // 已有 i, 缓冲区内有 j, 剩余 k 步
        if(k == 0) return 0;
        int key = hash(i, j);
        if(dp[key][k] != 0)
            return dp[key][k];
        int ans = 1 + solve(i + 1, j, k - 1, dp, N);
        ans = max(ans, j + solve(i + j, j, k - 1, dp, N));
        if(k >= 3)
            ans = max(ans, i + solve(i + i, i, k - 3, dp, N));
        return dp[key][k] = ans;
    }

    int hash(int i, int j)
    {
        return i * 100 + j;
    }
};

// dp[i]
class Solution_4 {
public:
    int maxA(int N) {
        if(N == 0) return 0;
        vector<int> dp(max(4, N + 1));
        dp[1] = 1;
        for(int i = 2; i <= N; ++i)
        {
            dp[i] = dp[i - 1] + 1;
            for(int j = 3; j <= i - 2; ++j)
            {
                dp[i]= max(dp[i], dp[i - j] * (j - 1));
            }
        }
        return dp[N];
    }
};

