import functools

MOD = int(1e9 + 7)

class Solution:
    def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
        self.m = m
        self.n = n
        self.dx = [0, 1, 0, -1]
        self.dy = [1, 0, -1, 0]
        if maxMove == 0:
            return 0
        return self.dfs(startRow, startColumn, maxMove)

    @functools.lru_cache(int(1e8))
    def dfs(self, i, j, k):
        if i < 0 or i >= self.m or j < 0 or j >= self.n:
            return 1
        if k == 0:
            return 0
        ans = 0
        for d in range(4):
            x = i + self.dx[d]
            y = j + self.dy[d]
            ans = (ans + self.dfs(x, y, k - 1)) % MOD
        return ans

