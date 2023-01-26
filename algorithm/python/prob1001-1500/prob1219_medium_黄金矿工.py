class Solution:
    dx = [1, -1, 0, 0]
    dy = [0, 0, 1, -1]

    def getMaximumGold(self, grid: List[List[int]]) -> int:
        self.grid = grid
        n = len(grid)
        m = len(grid[0])
        ans = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 0:
                    continue
                ans = max(ans, self.dfs(i, j))
        return ans

    def dfs(self, i: int, j: int) -> int:
        n = len(self.grid)
        m = len(self.grid[0])
        max_ = 0
        tmp = self.grid[i][j]
        self.grid[i][j] = 0
        for d in range(4):
            x = i + self.__class__.dx[d]
            y = j + self.__class__.dy[d]
            if x < 0 or x >= n or y < 0 or y >= m:
                continue
            if self.grid[x][y] == 0:
                continue
            max_ = max(max_, self.dfs(x, y))
        self.grid[i][j] = tmp
        return max_ + self.grid[i][j]
