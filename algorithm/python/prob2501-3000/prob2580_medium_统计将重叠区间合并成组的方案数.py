MOD = int(1e9 + 7)

def mykey(r):
    return r[0]

class Solution:
    def countWays(self, ranges: List[List[int]]) -> int:
        ranges.sort(key=mykey)
        n = len(ranges)
        i = 0
        x = 0
        while i < n:
            l = ranges[i][0]
            r = ranges[i][1]
            while i < n and ranges[i][0] <= r:
                r = max(r, ranges[i][1])
                i += 1
            x += 1
        return (2 ** x) % MOD

