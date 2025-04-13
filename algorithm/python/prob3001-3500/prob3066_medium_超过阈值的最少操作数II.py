import heapq

class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        n = len(nums)
        data = nums
        heapq.heapify(data)
        ans = 0
        while len(data) >= 2 and heapq.nsmallest(1, data)[0] < k:
            ans += 1
            x = heapq.heappop(data)
            y = heapq.heappop(data)
            heapq.heappush(data, min(x, y) * 2 + max(x, y))
        return ans
