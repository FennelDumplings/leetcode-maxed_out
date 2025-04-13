from collections import deque

class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        filtered = filter(lambda x: x < k, nums)
        ans = 0
        for _ in filtered:
            ans += 1
        return ans
