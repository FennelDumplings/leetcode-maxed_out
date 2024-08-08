class Solution:
    def maxOperations(self, nums: List[int]) -> int:
        n = len(nums)
        if n < 2:
            return 0
        s = nums[0] + nums[1]
        ans = 1
        i = 2
        for i in range(2, n, 2):
            if i == n - 1 or nums[i] + nums[i + 1] != s:
                break
            else:
                ans += 1
        return ans
