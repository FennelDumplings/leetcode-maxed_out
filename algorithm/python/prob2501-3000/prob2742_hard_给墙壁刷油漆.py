from functools import lru_cache

class Solution:
    def paintWalls(self, cost: List[int], time: List[int]) -> int:
        n = len(cost)
        INF = int(1e9)

        @lru_cache(int(1e8))
        def solve(i: int, j: int) -> int:
            if i == 0:
                if time[0] + 1 < j:
                    return INF
                elif j <= 0:
                    return 0
                else:
                    return cost[0]

            if j <= 0:
                return 0

            return min(cost[i] + solve(i - 1, j - time[i] - 1), solve(i - 1, j))

        return solve(n - 1, n)
