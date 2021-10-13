class Solution:
    def subtractProductAndSum(self, n: int) -> int:
        p = 1
        s = 0
        while n > 0:
            d = n % 10
            p *= d
            s += d
            n //= 10
        return p - s
