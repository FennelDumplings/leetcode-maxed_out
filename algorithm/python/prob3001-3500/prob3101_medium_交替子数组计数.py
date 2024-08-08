class Solution:
    def countAlternatingSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        prev = 1
        ans = 1
        for i in range(1, n):
            ans += 1
            if nums[i] != nums[i - 1]:
                ans += prev
                prev += 1
            else:
                prev = 1
        return ans
