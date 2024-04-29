class Solution:
    def maxArrayValue(self, nums: List[int]) -> int:
        s = nums[-1]
        for i in range(len(nums) - 2, -1, -1):
            s = s + nums[i] if nums[i] <= s else nums[i]
        return s
