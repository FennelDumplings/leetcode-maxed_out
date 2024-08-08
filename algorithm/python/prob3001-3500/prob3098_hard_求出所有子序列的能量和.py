from functools import lru_cache

MOD = int(1e9 + 7)

class Solution:
    def sumOfPowers(self, nums: List[int], k: int) -> int:
        n = len(nums)
        nums.sort()
        INF = nums[-1] - nums[0]

        @lru_cache(int(1e8))
        def solve(i: int , j: int, d: int) -> int:
            if j == k:
                return 0
            if k - j > n - i:
                return 0
            if j + 1 == k:
                return d
            r = 0
            for t in range(i + 1, n):
                r = (r + solve(t, j + 1, min(d, nums[t] - nums[i]))) % MOD
            return r

        ans = 0
        for i in range(n):
            ans = (ans + solve(i, 0, INF)) % MOD
        return ans

