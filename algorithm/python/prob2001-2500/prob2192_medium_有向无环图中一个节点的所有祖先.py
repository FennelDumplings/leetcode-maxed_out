class Solution:
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        rg = [[] for _ in range(n)]
        indegrees = [0] * n
        for u, v in edges:
            rg[v].append(u)
            indegrees[u] += 1

        result = [set() for _ in range(n)]

        def dfs(u: int) -> List[int]:
            if result[u]:
                return
            for v in rg[u]:
                result[u].add(v)
                dfs(v)
                result[u].update(result[v])

        for u in range(n):
            if indegrees[u] != 0:
                continue
            dfs(u)

        for i in range(n):
            result[i] = list(result[i])
            result[i].sort()

        return result
