class Solution:
    def findValueOfPartition(self, nums: List[int]) -> int:
        nums.sort()
        n = len(nums)
        ans = nums[n - 1] - nums[0]
        for i in range(n - 1):
            ans = min(ans, nums[i + 1] - nums[i])
        return ans

