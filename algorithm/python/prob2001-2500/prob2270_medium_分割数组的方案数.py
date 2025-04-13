class Solution:
    def waysToSplitArray(self, nums: List[int]) -> int:
        n = len(nums)
        sums = [0] * (n + 1)
        for i in range(1, n + 1):
            sums[i] = sums[i - 1] + nums[i -  1]
        ans = 0
        for i in range(n - 1):
            if sums[i + 1] >= sums[n] - sums[i + 1]:
                ans += 1
        return ans
