class Solution:
    def minimumAverage(self, nums: List[int]) -> float:
        n = len(nums)
        nums.sort()
        l = 0
        r = n - 1
        ans = (nums[l] + nums[r]) / 2
        while l < r:
            ans = min(ans, (nums[l] + nums[r]) / 2)
            l += 1
            r -= 1
        return ans

