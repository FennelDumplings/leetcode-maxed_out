import numpy as np

INF = int(1e9)

class Solution:
    def maxScore(self, grid: List[List[int]]) -> int:
        n = len(grid)
        m = len(grid[0])

        dp = [[-INF for _ in range(m)] for _ in range(n)]
        row_max = [[-INF for _ in range(m)] for _ in range(n)]
        col_max = [[-INF for _ in range(m)] for _ in range(n)]

        row_max[n - 2][m - 1] = grid[n - 1][m - 1]
        col_max[n - 1][m - 2] = grid[n - 1][m - 1]

        for x in range(n - 1, -1, -1):
            for y in range(m - 1, -1, -1):
                if x == n - 1 and y == m - 1:
                    continue
                dp[x][y] = max(row_max[x][y], col_max[x][y]) - grid[x][y]
                if x > 0:
                    row_max[x - 1][y] = max(dp[x][y] + grid[x][y], grid[x][y])
                if y > 0:
                    col_max[x][y - 1] = max(dp[x][y] + grid[x][y], grid[x][y])
        return max([max(row) for row in dp])
