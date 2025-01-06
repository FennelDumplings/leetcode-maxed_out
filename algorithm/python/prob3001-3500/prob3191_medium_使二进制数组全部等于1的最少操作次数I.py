class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0
        for i in range(n - 2):
            if nums[i] == 1:
                continue
            ans += 1
            nums[i + 1] ^= 1
            nums[i + 2] ^= 1
        if nums[i + 1] == 1 and nums[i + 2] == 1:
            return ans
        else:
            return -1

