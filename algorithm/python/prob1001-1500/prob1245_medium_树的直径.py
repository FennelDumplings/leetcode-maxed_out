class Solution:
    def treeDiameter(self, edges: List[List[int]]) -> int:
        n = len(edges)
        print(n)
        self.g = [[] for i in range(n + 1)]
        for e in edges:
            self.g[e[0]].append(e[1])
            self.g[e[1]].append(e[0])
        self.ans = 0
        self.dfs(0, -1)
        return self.ans

    def dfs(self, u, fa):
        max1 = max2 = 0
        for v in self.g[u]:
            if v != fa:
                t = self.dfs(v, u) + 1
                if max1 < t:
                    max2 = max1
                    max1 = t
                elif max2 < t:
                    max2 = t
        self.ans = max(self.ans, (max1 + max2))
        return max1
