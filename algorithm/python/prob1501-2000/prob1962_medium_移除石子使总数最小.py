import heapq
import math

class Solution:
    def minStoneSum(self, piles: List[int], k: int) -> int:
        n = len(piles)
        for i in range(n):
            piles[i] = -piles[i]
        heapq.heapify(piles)
        while k > 0:
            x = -heapq.heappop(piles)
            x -= math.floor(x / 2)
            if x > 0:
                heapq.heappush(piles, -x)
            k -= 1
        return -sum(piles)
