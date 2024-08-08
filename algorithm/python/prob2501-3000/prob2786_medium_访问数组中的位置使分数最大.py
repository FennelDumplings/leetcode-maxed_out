INF = int(1e9)

class Solution:
    def maxScore(self, nums: List[int], x: int) -> int:
        n = len(nums)
        dp = [-INF / 2] * n
        dp[0] = nums[0]
        mx_odd = -INF
        mx_even = -INF
        if nums[0] % 2 == 1:
            mx_odd = dp[0]
        else:
            mx_even = dp[0]

        for j in range(1, n):
            if nums[j] % 2 == 1:
                if mx_odd != -INF:
                    dp[j] = max(dp[j], nums[j] + mx_odd)
                if mx_even != -INF:
                    dp[j] = max(dp[j], nums[j] + mx_even - x)
                mx_odd = max(mx_odd, dp[j])
            else:
                if mx_odd != -INF:
                    dp[j] = max(dp[j], nums[j] + mx_odd - x)
                if mx_even != -INF:
                    dp[j] = max(dp[j], nums[j] + mx_even)
                mx_even = max(mx_even, dp[j])

        return max(dp)
