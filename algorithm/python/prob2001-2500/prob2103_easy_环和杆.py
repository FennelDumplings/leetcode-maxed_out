class Solution:
    def countPoints(self, rings: str) -> int:
        n = len(rings)
        i = 0
        states = [set() for _ in range(10)]
        while i < n:
            color = rings[i]
            pos = int(rings[i + 1])
            states[pos].insert(color)
            i += 2
        ans = 0
        for s in states:
            if len(s) == 3:
                ans += 1
        return ans
