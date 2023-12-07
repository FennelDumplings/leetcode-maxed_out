class Solution:
    def longestAlternatingSubarray(self, nums: List[int], threshold: int) -> int:
        n = len(nums)
        ans = 0
        left = 0
        while left < n:
            if nums[left] > threshold or nums[left] % 2 == 1:
                left += 1
                continue
            right = left
            while right < n and nums[right] <= threshold and nums[right] % 2 == (right - left) % 2:
                right += 1
            ans = max(ans, right - left)
            left = right
        return ans
