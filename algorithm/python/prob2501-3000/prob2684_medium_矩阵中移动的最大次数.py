import functools

class Solution:
    def maxMoves(self, grid: List[List[int]]) -> int:
        self.grid = grid
        self.m = len(grid)
        self.n = len(grid[0])
        ans = 0

        for i in range(self.m):
            ans = max(ans, self.dp(i, 0))
        return ans

    @functools.lru_cache(int(1e8))
    def dp(self, i: int, j: int) -> int:
        if j == self.n - 1:
            return 0
        ans = 0
        for t in (-1, 0, 1):
            if i + t < 0 or i + t >= self.m:
                continue
            if self.grid[i][j] >= self.grid[i+t][j+1]:
                continue
            ans = max(ans, 1 + self.dp(i + t, j + 1))
        return ans
