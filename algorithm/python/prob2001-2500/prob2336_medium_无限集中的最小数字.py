import heapq

class SmallestInfiniteSet:
    def __init__(self):
        self.heap = []
        self.setting = set()
        heapq.heappush(self.heap, 1)

    def popSmallest(self) -> int:
        smallest = heapq.heappop(self.heap)
        self.setting.add(smallest)
        if len(self.heap) == 0:
            heapq.heappush(self.heap, smallest + 1)
        return smallest

    def addBack(self, num: int) -> None:
        if(num not in self.setting):
            return
        self.setting.remove(num)
        heapq.heappush(self.heap, num)
