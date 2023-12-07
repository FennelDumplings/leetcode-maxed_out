class Solution:
    def minPathCost(self, grid: List[List[int]], moveCost: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        INF = int(1e9)
        dp = [[INF for j in range(n)] for i in range(m)]
        for j in range(n):
            dp[0][j] = grid[0][j]
        for i in range(1, m):
            for j in range(n):
                for k in range(n):
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + moveCost[grid[i - 1][k]][j])
                dp[i][j] += grid[i][j]
        return min(dp[m - 1])
