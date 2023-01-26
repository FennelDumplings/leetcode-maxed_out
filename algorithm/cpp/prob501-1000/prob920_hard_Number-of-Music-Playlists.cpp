// prob920: Number of Music Playlists

/*
 * https://leetcode-cn.com/problems/number-of-music-playlists/
 */

#include <vector>

using namespace std;

class Solution_2 {
public:
    int numMusicPlaylists(int N, int L, int K) {
        int MOD = 1e9 + 7;
        using ll = long long;
        vector<vector<int>> dp(L + 1, vector<int>(N + 1));
        dp[0][0] = 1;
        // dp[i][j] := 列表长 i, 含 j 首不同歌曲
        // i >= j
        for(int i = 1; i <= L; ++i)
            for(int j = 1; j <= min(N, i); ++j)
            {
                dp[i][j] = ((ll)dp[i][j] + (ll)dp[i - 1][j] * max(j - K, 0)) % MOD;
                dp[i][j] = ((ll)dp[i][j] + (ll)dp[i - 1][j - 1] * (N - j + 1)) % MOD;
            }
        return dp[L][N];
    }
};

// 先计算不一定每首歌至少播放一次的答案，再通过容斥原理减去歌没放全的答案。
class Solution {
public:
    int numMusicPlaylists(int N, int L, int K) {
        // 0 <= K < N <= L <= 100
        vector<vector<ll>> combine(L + 1, vector<ll>(L + 1, 1)); // 预处理组合数组
        for(int i = 1; i <= L; ++i) // 杨辉三角递推
        {
            for(int j = 1; j <= L; ++j)
            {
                combine[i][j] = combine[i - 1][j] + combine[i][j - 1];
                combine[i][j] %= MOD;
            }
        }
        vector<ll> dp(L + 1);
        dp[K] = solve(K, L, K);
        for(int i = K + 1; i <= N; ++i) // 根据容斥原理计算每首都放的答案
        {
            dp[i] = solve(i, L, K);
            for(int j = K; j < i; ++j)
                dp[i] -= ((combine[j][i - j] * dp[j]) % MOD);   // combine[j][i - j] 的值为 C(i,j)
            dp[i] = (dp[i] + MOD) % MOD;
        }
        return (dp[N] + MOD) % MOD;
    }

    int solve(int N, int L, int K)
    {
        // 计算不一定每首都放的答案
        vector<ll> dp(L);
        dp[0] = N;
        for(int i = 1; i < K + 1; ++i)
        {
            dp[i] = dp[i - 1] * (N - i);
            dp[i] %= MOD;
        }
        for(int i = K + 1; i < L; ++i)
        {
            dp[i] = dp[i - 1] * (N - K);
            dp[i] %= MOD;
        }
        return dp[L - 1];
    }

private:
    const int MOD = 1e9 + 7;
    using ll = long long;
};
