def func_g1(n):
    if n % 2 == 0:
        return n * n // 4
    else:
        return (n + 1) * (n + 1) // 4

def func_g2(n):
    if n % 2 == 0:
        return n * (n + 2) // 4
    else:
        return (n - 1) * (n + 1) // 4

class Solution:
    def maxHeightOfTriangle(self, red: int, blue: int) -> int:
        left = 0
        right = int(1e10)
        while left < right:
            mid = (left + right + 1) // 2
            g1 = func_g1(mid)
            g2 = func_g2(mid)
            if min(red, blue) >= min(g1, g2) and max(red, blue) >= max(g1, g2):
                left = mid
            else:
                right = mid - 1
        return left
