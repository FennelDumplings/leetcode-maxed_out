import heapq

class Solution:
    def mostCompetitive(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        result = []
        left = 0
        right = n - k
        data = [(nums[i], i) for i in range(left, right)]
        heapq.heapify(data)
        for _ in range(k):
            heapq.heappush(data, (nums[right], right))
            while data[0][1] < left:
                heappop(data)
            smallest = heappop(data)
            result.append(smallest[0])
            left = smallest[1] + 1
            right += 1
        return result
