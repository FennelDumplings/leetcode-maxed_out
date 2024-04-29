INF = int(1e10)

class Solution:
    def minimumSum(self, nums: List[int]) -> int:
        n = len(nums)
        # L[i] := nums[0..i] 中的最小值
        # R[i] := nums[i..n-1] 中的最小值
        L = [INF] * n
        R = [INF] * n
        L[0] = nums[0]
        for i in range(1, n):
            L[i] = min(nums[i], L[i - 1])
        R[n - 1] = nums[n - 1]
        for i in range(n - 2, -1, -1):
            R[i] = min(nums[i], R[i + 1])
        ans = INF
        for i in range(1, n - 1):
            if L[i - 1] < nums[i] and R[i + 1] < nums[i]:
                ans = min(ans, L[i - 1] + nums[i] + R[i + 1])
        return ans if ans != INF else -1
