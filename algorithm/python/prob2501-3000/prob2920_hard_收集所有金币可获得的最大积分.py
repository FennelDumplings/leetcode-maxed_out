from functools import lru_cache

class Solution:
    def maximumPoints(self, edges: List[List[int]], coins: List[int], k: int) -> int:
        n = len(coins)
        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        @lru_cache(maxsize=int(1e7))
        def solve(fa: int, u: int, j: int) -> int:
            ans1 = (coins[u] >> j) - k
            ans2 = coins[u] >> (j + 1)
            for v in graph[u]:
                if v == fa:
                    continue
                ans1 += solve(u, v, j)
                if j <= 14:
                    ans2 += solve(u, v, j + 1)
            return max(ans1, ans2)

        return solve(-1, 0, 0)
