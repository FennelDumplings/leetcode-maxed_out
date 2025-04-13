from functools import lru_cache

class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        n = len(prices)

        @lru_cache(maxsize=int(1e7))
        def solve(i: int, j: int) -> int:
            if j > n:
                return 0
            # 买 i
            ans = prices[i - 1] + solve(i + 1, max(j, i * 2 + 1))
            # 不买 i
            if i < j:
                ans = min(ans, solve(i + 1, j))
            return ans

        return solve(1, 1)
