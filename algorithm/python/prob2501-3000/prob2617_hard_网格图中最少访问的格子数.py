import heapq

INF = int(1e10)

class Item:
    def __init__(self, dp, idx):
        # 对于 row_heaps[i], idx 代表 j
        # 对于 col_heaps[j], idx 代表 i
        self.dp = dp
        self.idx = idx

    def __lt__(self, other):
        return self.dp < other.dp

class Solution:
    def minimumVisitedCells(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        row_heaps = [[] for _ in range(m)]
        col_heaps = [[] for _ in range(n)]

        dp = [[-1 for _ in range(n)] for _ in range(m)]
        dp[0][0] = 0
        heapq.heappush(row_heaps[0], Item(dp[0][0], 0))
        heapq.heappush(col_heaps[0], Item(dp[0][0], 0))

        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                minx = INF
                while row_heaps[i]:
                    top_item = row_heaps[i][0]
                    if top_item.idx + grid[i][top_item.idx] < j:
                        heapq.heappop(row_heaps[i])
                    else:
                        minx = min(minx, top_item.dp)
                        break
                while col_heaps[j]:
                    top_item = col_heaps[j][0]
                    if top_item.idx + grid[top_item.idx][j] < i:
                        heapq.heappop(col_heaps[j])
                    else:
                        minx = min(minx, top_item.dp)
                        break
                if minx != INF:
                    dp[i][j] = minx + 1
                if dp[i][j] != -1:
                    heapq.heappush(row_heaps[i], Item(dp[i][j], j))
                    heapq.heappush(col_heaps[j], Item(dp[i][j], i))

        return dp[m-1][n-1] + 1 if dp[m-1][n-1] != -1 else -1
