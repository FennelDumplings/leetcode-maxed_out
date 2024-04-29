INF = 1e11

def gap(x: int, p: int) -> int:
    m = x % p
    return m if m == 0 else p - m

class Solution:
    def minSkips(self, dist: List[int], speed: int, hoursBefore: int) -> int:
        n = len(dist)
        dist = [x * speed for x in dist]
        dp = [[INF for _ in range(n)] for _ in range(n)]
        dp[0][0] = dist[0]
        for i in range(1, n):
            t = dist[i]
            for k in range(i + 1):
                if k < i:
                    dp[i][k] = min(dp[i][k], dp[i - 1][k] + gap(dp[i - 1][k], speed) + t)
                if 0 < k:
                    dp[i][k] = min(dp[i][k], dp[i - 1][k - 1] + t)
        ans = -1
        for k in range(n):
            if dp[n - 1][k] <= hoursBefore * speed:
                ans = k
                break
        return ans
