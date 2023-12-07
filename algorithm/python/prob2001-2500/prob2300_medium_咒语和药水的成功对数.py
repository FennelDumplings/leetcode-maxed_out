import bisect

def func(s):
    def _func(x: int) -> int:
        return x * s
    return _func

class Solution:
    def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:
        n = len(spells)
        m = len(potions)
        potions.sort()
        result = [0 for _ in range(n)]
        for i, s in enumerate(spells):
            myfunc = func(s)
            k = bisect_left(potions, success, key=myfunc)
            result[i] = m - k
        return result
