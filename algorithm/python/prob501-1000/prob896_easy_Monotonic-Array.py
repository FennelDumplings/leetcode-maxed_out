class Solution:
    def isMonotonic(self, nums: List[int]) -> bool:
        n = len(nums)
        if n <= 2:
            return True
        i = 1
        while i < n and nums[i] - nums[i - 1] == 0:
            i += 1
        if i >= n - 1:
            return True
        diff = nums[i] - nums[i - 1]
        i += 1
        while i < n:
            if (nums[i] - nums[i - 1]) * diff >= 0:
                i += 1
            else:
                return False
        return True
