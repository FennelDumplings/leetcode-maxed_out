class Solution:
    def minCapability(self, nums: List[int], k: int) -> int:
        # check(mid) 返回最大金额为 mid 时，最多可以偷多少房子
        def check(mid: int) -> int:
            dp0 = dp1 = 0
            for num in nums:
                if num > mid:
                    dp0 = dp1
                else:
                    dp0, dp1 = dp1, max(dp1, dp0 + 1)
            return dp1
        return bisect_left(range(max(nums)), k, key=check)
