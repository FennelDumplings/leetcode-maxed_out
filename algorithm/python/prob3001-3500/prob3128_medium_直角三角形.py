class Solution:
    def numberOfRightTriangles(self, grid: List[List[int]]) -> int:
        n = len(grid)
        m = len(grid[0])
        rows = [0] * n
        cols = [0] * m
        for i in range(n):
            for j in range(m):
                rows[i] += grid[i][j]
                cols[j] += grid[i][j]
        ans = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 1:
                    ans += (rows[i] - 1) * (cols[j] - 1)
        return ans

