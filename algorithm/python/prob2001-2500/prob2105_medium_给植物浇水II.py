class Solution:
    def minimumRefill(self, plants: List[int], capacityA: int, capacityB: int) -> int:
        n = len(plants)
        l = 0
        r = n - 1
        ans = 0
        xA = capacityA
        xB = capacityB
        while l < r:
            if xA < plants[l]:
                ans += 1
                xA = capacityA
            xA -= plants[l]
            l += 1
            if xB < plants[r]:
                ans += 1
                xB = capacityB
            xB -= plants[r]
            r -= 1
        if l == r:
            if max(xA, xB) < plants[l]:
                ans += 1
        return ans

