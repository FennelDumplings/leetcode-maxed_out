class Solution:
    def countWays(self, nums: List[int]) -> int:
        nums.sort()
        n = len(nums)
        ans = 0
        if 0 < nums[0]:
            ans += 1
        for c in range(1, n):
            if nums[c - 1] < c and nums[c] > c:
                ans += 1
        if nums[n - 1] < n:
            ans += 1
        return ans
