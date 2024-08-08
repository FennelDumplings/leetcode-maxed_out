from functools import lru_cache

class Solution:
    def maxOperations(self, nums: List[int]) -> int:
        @lru_cache(int(1e8))
        def solve(i, j, s):
            if i == j or j == i - 1:
                return 0
            ans = 0
            if nums[i] + nums[i + 1] == s:
                ans = max(ans, 1 + solve(i + 2, j, s))
            if nums[i] + nums[j] == s:
                ans = max(ans, 1 + solve(i + 1, j - 1, s))
            if nums[j - 1] + nums[j] == s:
                ans = max(ans, 1 + solve(i, j - 2, s))
            return ans

        n = len(nums)
        ans = 0
        ans = max(ans, solve(0, n - 1, nums[0] + nums[1]))
        ans = max(ans, solve(0, n - 1, nums[0] + nums[-1]))
        ans = max(ans, solve(0, n - 1, nums[-2] + nums[-1]))
        return ans
