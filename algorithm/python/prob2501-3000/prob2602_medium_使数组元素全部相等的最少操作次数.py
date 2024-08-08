import bisect

class Solution:
    def minOperations(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        nums.sort()
        sums = [0] * (n + 1)
        for i in range(1, n + 1):
            sums[i] = sums[i - 1] + nums[i - 1]
        m = len(queries)
        result = [-1] * m
        for j in range(m):
            y = queries[j]
            k = bisect.bisect(nums, y)
            result[j] = (k * 2 - n) * y + sums[n] - 2 * sums[k]
        return result
