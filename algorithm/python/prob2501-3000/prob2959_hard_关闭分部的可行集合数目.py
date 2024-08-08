INF = int(1e9)

class Solution:
    def numberOfSets(self, n: int, maxDistance: int, roads: List[List[int]]) -> int:
        def floyd(s: int) -> int:
            d = [[INF for _ in range(n)] for _ in range(n)]
            for i in range(n):
                if (s >> i) & 1 == 0:
                    continue
                for j in range(n):
                    if (s >> j) & 1 == 0:
                        continue
                    d[i][j] = adj[i][j]
            for k in range(n):
                if (s >> k) & 1 == 0:
                    continue
                for i in range(n):
                    if (s >> i) & 1 == 0:
                        continue
                    for j in range(n):
                        if (s >> j) & 1 == 0:
                            continue
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j])
            for i in range(n):
                if (s >> i) & 1 == 0:
                    continue
                for j in range(n):
                    if (s >> j) & 1 == 0:
                        continue
                    if d[i][j] > maxDistance:
                        return 0
            return 1

        adj = [[INF for _ in range(n)] for _ in range(n)]
        for u, v, w in roads:
            adj[u][v] = min(adj[u][v], w)
            adj[v][u] = min(adj[v][u], w)
        ans = 0
        for i in range(n):
            adj[i][i] = 0
        for s in range(1 << n):
            ans += floyd(s)
        return ans
