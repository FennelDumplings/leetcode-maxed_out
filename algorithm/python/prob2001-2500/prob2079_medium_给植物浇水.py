class Solution:
    def wateringPlants(self, plants: List[int], capacity: int) -> int:
        n = len(plants)
        pos = -1
        x = capacity
        step = 0
        while pos < n - 1:
            while pos + 1 < n and x >= plants[pos + 1]:
                pos += 1
                x -= plants[pos]
                step += 1
            if pos == n - 1:
                break
            step += (pos + 1) * 2
            x = capacity
        return step

