class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        dp = [False] * (n + 1)
        dp[0] = True
        dp[2] = nums[0] == nums[1]
        for i in range(3, n + 1):
            dp[i] = (dp[i - 2] and (nums[i - 1] == nums[i - 2])) or \
                    (dp[i - 3] and (nums[i - 1] == nums[i - 2] == nums[i - 3] or
                                    nums[i - 1] == nums[i - 2] + 1 == nums[i - 3] + 2))
        return dp[n]
