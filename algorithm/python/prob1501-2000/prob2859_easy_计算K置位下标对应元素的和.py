def ones(x: int) -> int:
    cnt = 0
    while x:
        x = x & (x - 1)
        cnt += 1
    return cnt

class Solution:
    def sumIndicesWithKSetBits(self, nums: List[int], k: int) -> int:
        ans = 0
        for i, x in enumerate(nums):
            if ones(i) == k:
                ans += x
        return ans
