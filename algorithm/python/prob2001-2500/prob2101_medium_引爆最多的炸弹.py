class Solution:
    def maximumDetonation(self, bombs: List[List[int]]) -> int:
        def dfs(u: int) -> int:
            cnt = 1
            for v in g[u]:
                if visited[v] == 1:
                    continue
                visited[v] = 1
                cnt += dfs(v)
            return cnt

        n = len(bombs)
        g = [[] for _ in range(n)]
        for i in range(n):
            xi, yi, ri = bombs[i]
            for j in range(i + 1, n):
                xj, yj, rj = bombs[j]
                dist = pow(xi - xj, 2) + pow(yi - yj, 2)
                if pow(ri, 2) >= dist:
                    g[i].append(j)
                if pow(rj, 2) >= dist:
                    g[j].append(i)
        visited = [0] * n
        ans = 0
        for s in range(n):
            if visited[s] == 1:
                continue
            visited[s] = 1
            ans = max(ans, dfs(s))
        return ans
