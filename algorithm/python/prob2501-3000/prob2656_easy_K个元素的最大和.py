class Solution:
    def maximizeSum(self, nums: List[int], k: int) -> int:
        M = max(nums)
        return (M + M + k - 1) * k // 2
