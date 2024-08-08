class Solution:
    def sumOfTheDigitsOfHarshadNumber(self, x: int) -> int:
        s = 0
        t = x
        while t > 0:
            s += t % 10
            t //= 10
        if x % s == 0:
            return s
        return -1
