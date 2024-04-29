MOD = int(1e9 + 7)

class Solution:
    def countPaths(self, n: int, roads: List[List[int]]) -> int:
        INF = int(1e12)
        self.dp = [[INF  for _ in range(n)] for _ in range(n)]
        self.g = [[] for _ in range(n)]
        for s, t, w in roads:
            self.dp[s][t] = w
            self.dp[t][s] = w
            self.g[s].append((t, w))
            self.g[t].append((s, w))
        for i in range(n):
            self.dp[i][i] = 0
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    self.dp[i][j] = min(self.dp[i][j], self.dp[i][k] + self.dp[k][j])
        self.dp_cnt = [-1 for _ in range(n)]
        self.dp_cnt[n - 1] = 1
        return self.solve(0, n - 1)

    def solve(self, u, t):
        # 从 u 到 t，最短路径的条数
        if self.dp_cnt[u] != -1:
            return self.dp_cnt[u]
        self.dp_cnt[u] = 0
        for v, w in self.g[u]:
            if w + self.dp[v][t] == self.dp[u][t]:
                self.dp_cnt[u] = (self.dp_cnt[u] + self.solve(v, t)) % MOD
        return self.dp_cnt[u]
