from queue import Queue

class Solution:
    def maximumMinutes(self, grid: List[List[int]]) -> int:
        n = len(grid)
        m = len(grid[0])
        dx = [1, -1, 0, 0]
        dy = [0, 0, 1, -1]

        def bfs(ps: List[Tuple[int, int]]):
            # BFS 最短路径
            f = [[int(1e9) for _ in range(m)] for _ in range(n)]
            q = Queue() # 队列中的内容：i, j
            for s in ps:
                f[s[0]][s[1]] = 0
                q.put((s[0], s[1]))
            while not q.empty():
                i, j = q.get()
                t = f[i][j]
                for d in range(4):
                    nxt_i = i + dx[d]
                    nxt_j = j + dy[d]
                    if nxt_i < 0 or nxt_i >= n or nxt_j < 0 or nxt_j >= m:
                        continue
                    if grid[nxt_i][nxt_j] != 0:
                        continue
                    if f[nxt_i][nxt_j] != int(1e9):
                        continue
                    f[nxt_i][nxt_j] = t + 1
                    q.put((nxt_i, nxt_j))
            return f

        # 预处理 f
        # f[i][j] := (i, j) 有火的时间，即最短路径的距离
        source_points = []
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 1:
                    source_points.append((i, j))
        f = bfs(source_points)

        # 预处理 p
        p = bfs([(0, 0)])

        if p[n - 1][m - 1] == int(1e9):
            return -1
        if f[n - 1][m - 1] == int(1e9):
            return int(1e9)
        delta = f[n - 1][m - 1] - p [n - 1][m - 1]
        if delta < 0:
            return -1
        if f[n - 2][m - 1] - p[n - 2][m - 1] > delta or f[n - 1][m - 2] - p[n - 1][m - 2] > delta:
            return delta
        return delta - 1
