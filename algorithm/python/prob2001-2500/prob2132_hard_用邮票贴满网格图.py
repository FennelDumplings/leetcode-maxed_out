class Solution:
    def possibleToStamp(self, grid: List[List[int]], stampHeight: int, stampWidth: int) -> bool:
        n = len(grid)
        m = len(grid[0])

        sums = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                sums[i][j] = grid[i - 1][j - 1] + sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1]

        diff = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        for i in range(n - stampHeight + 1):
            for j in range(m - stampWidth + 1):
                x1 = i
                y1 = j
                x2 = i + stampHeight - 1
                y2 = j + stampWidth - 1
                if sums[x2 + 1][y2 + 1] - sums[x2 + 1][y1] - sums[x1][y2 + 1] + sums[x1][y1] == 0:
                    diff[x1][y1] += 1
                    diff[x2 + 1][y1] -= 1
                    diff[x1][y2 + 1] -= 1
                    diff[x2 + 1][y2 + 1] += 1

                    # print(diff)

        visited = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        visited[0][0] = diff[0][0]
        for i in range(1, n + 1):
            visited[i][0] = diff[i][0] + visited[i - 1][0]
        for j in range(1, m + 1):
            visited[0][j] = diff[0][j] + visited[0][j - 1]
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                visited[i][j] = diff[i][j] + visited[i][j - 1] + visited[i - 1][j] - visited[i - 1][j - 1]

        # print(visited)

        for i in range(n):
            for j in range(m):
                if grid[i][j] == 0 and visited[i][j] == 0:
                    return False
        return True
