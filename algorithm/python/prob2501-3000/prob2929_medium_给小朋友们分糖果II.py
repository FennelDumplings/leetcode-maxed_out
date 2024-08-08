import math

class Solution:
    def distributeCandies(self, n: int, l: int) -> int:
        k = 3
        ans = math.comb(n + k - 1, k - 1)
        ans -= 3 * math.comb((n + l + 1) + k - 1, k - 1)
        ans += 3 * math.comb((n + l * 2 + 2) + k - 1, k - 1)
        ans -= math.comb((n + l * 3 + 3) + k - 1, k - 1)
        return ans
