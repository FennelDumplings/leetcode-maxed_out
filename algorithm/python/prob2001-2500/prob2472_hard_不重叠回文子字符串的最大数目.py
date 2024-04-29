class Solution:
    def maxPalindromes(self, s: str, k: int) -> int:
        n = len(s)
        p = [[False for _ in range(n)] for _ in range(n)]
        for i in range(n):
            p[i][i] = True
        for i in range(n - 1):
            if s[i] == s[i + 1]:
                p[i][i + 1] = True
        for l in range(3, n + 1):
            for i in range(n - l + 1):
                j = i + l - 1
                if s[i] == s[j]:
                    p[i][j] = p[i + 1][j - 1]

        dp = [0 for _ in range(n + 1)]
        for j in range(1, n + 1):
            dp[j] = dp[j - 1]
            for i in range(j - k + 1):
                if p[i][j - 1]:
                    dp[j] = max(dp[j], 1 + dp[i])
        return dp[n]
