class Solution:
    def minRectanglesToCoverPoints(self, points: List[List[int]], w: int) -> int:
        xs = [x for x, _ in points]
        xs.sort()
        n = len(xs)
        p = 0
        ans = 0
        while p < n:
            ans += 1
            r = p
            while r < n and xs[r] - xs[p] <= w:
                r += 1
            p = r
        return ans
