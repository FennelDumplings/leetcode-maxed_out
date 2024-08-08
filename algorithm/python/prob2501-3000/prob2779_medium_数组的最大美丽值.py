class Event:
    def __init__(self, x, left):
        self.x = x
        self.left = left

    def __lt__(self, other):
        if self.x == other.x:
            return self.left < other.left
        return self.x < other.x

class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        events = []
        for x in nums:
            events.append(Event(x - k, 0))
            events.append(Event(x + k, 1))
        events.sort()
        s = 0
        ans = 0
        for e in events:
            if e.left == 0:
                s += 1
                ans = max(ans, s)
            else:
                s -= 1
        return ans
