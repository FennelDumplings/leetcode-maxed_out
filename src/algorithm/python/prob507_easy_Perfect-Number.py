import math

class Solution:
    def checkPerfectNumber(self, num: int) -> bool:
        if num == 1:
            return False
        s = 1;
        for i in range(2, int(sqrt(num)) + 1):
            if num % i == 0:
                s += i
                s += num / i
        return s == num
