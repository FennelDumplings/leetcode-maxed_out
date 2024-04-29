class Solution:
    def distinctIntegers(self, n: int) -> int:
        if n == 1:
            return n
        else:
            return n - 1
