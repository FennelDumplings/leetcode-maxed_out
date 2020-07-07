// prob920: Number of Music Playlists

/*
 * https://leetcode-cn.com/problems/number-of-music-playlists/
 */

#include <vector>

using namespace std;

class Solution {
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
