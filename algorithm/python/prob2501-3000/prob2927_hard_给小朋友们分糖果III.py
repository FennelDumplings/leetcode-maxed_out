
import math

def b(k, n):
    return math.comb(n + k - 1, k - 1)

class Solution:
    def distributeCandies(self, n: int, l: int) -> int:
        ans = b(3, n)
        if n - (l + 1) >= 0:
            ans -= b(3, n - (l + 1)) * 3
        if n - (l + 1) * 2 >= 0:
            ans += b(3, n - (l + 1) * 2) * 3
        if n - (l + 1) * 3 >= 0:
            ans -= b(3, n - (l + 1) * 3)
        return ans
