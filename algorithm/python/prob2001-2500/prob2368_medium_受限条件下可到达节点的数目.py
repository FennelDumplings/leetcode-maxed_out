class Solution:
    def reachableNodes(self, n: int, edges: List[List[int]], restricted: List[int]) -> int:
        self.g = [[] for _ in range(n)]
        for s, t in edges:
            self.g[s].append(t)
            self.g[t].append(s)
        self.setting = set(restricted)
        return self.dfs(0, -1)

    def dfs(self, u: int, fa: int) -> int:
        cnt = 1
        for v in self.g[u]:
            if v == fa:
                continue
            if v in self.setting:
                continue
            cnt += self.dfs(v, u)
        return cnt
