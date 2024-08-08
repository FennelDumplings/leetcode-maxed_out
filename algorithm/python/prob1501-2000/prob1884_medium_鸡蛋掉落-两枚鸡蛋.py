class Solution:
    def twoEggDrop(self, n: int) -> int:

        @lru_cache(int(1e8))
        def solve(k: int) -> int:
            if k == 0:
                return 0

            ans = k
            for j in range(1, k + 1):
                ans = min(ans, 1 + max(j - 1, solve(k - j)))

            return ans

        return solve(n)
