import math

class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        ans = 0
        for i in range(min(l, n) + 1):
            for j in range(min(l, n - i) + 1):
                if n - i - j <= l:
                    ans += 1
        return ans
