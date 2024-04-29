class Solution:
    def findChampion(self, n: int, edges: List[List[int]]) -> int:
        indegrees = [0] * n
        for u, v in edges:
            # u -> v
            indegrees[v] += 1
        cnt = 0
        root = -1
        for u in range(n):
            if indegrees[u] == 0:
                cnt += 1
                if cnt > 1:
                    return -1
                root = u
        return root
