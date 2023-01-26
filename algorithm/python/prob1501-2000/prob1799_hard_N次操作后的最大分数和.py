class Solution:
    def maxScore(self, nums: List[int]) -> int:
        self.nums = nums
        self.n = len(nums)
        return self.solve(0, 1)

    @lru_cache(int(1e7))
    def solve(self, state: int, r: int) -> int:
        ans = 0
        for i in range(self.n):
            if state >> i & 1:
                continue
            for j in range(i + 1, self.n):
                if state >> j & 1:
                    continue
                ans = max(ans, r * gcd(self.nums[i], self.nums[j]) + self.solve(state | (1 << i) | (1 << j), r + 1))
        return ans
