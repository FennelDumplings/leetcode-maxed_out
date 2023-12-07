from functools import lru_cache

class Solution:
    def minDeletion(self, nums: List[int]) -> int:
        self.n = len(nums)
        self.nums = nums
        ans = self.solve(0, 0)
        return ans

    @lru_cache(maxsize=int(1e6))
    def solve(self, i: int, k: int) -> int:
        if i == self.n - 1:
            if (self.n - 1) % 2 == k:
                return 1
            else:
                return 0

        # i < self.n - 1
        if self.nums[i] == self.nums[i + 1] and i % 2 == k:
            return self.solve(i + 1, (k + 1) % 2) + 1
        else:
            return min(self.solve(i + 1, (k + 1) % 2) + 1, self.solve(i + 1, k))

class Solution:
    def minDeletion(self, nums: List[int]) -> int:
        n = len(nums)
        cnt = 0
        i = 1
        while i < n:
            if (i - cnt) % 2 == 1 and nums[i] == nums[i - 1]:
                cnt += 1
            i += 1
        if (n - cnt) % 2 == 1:
            cnt += 1
        return cnt
