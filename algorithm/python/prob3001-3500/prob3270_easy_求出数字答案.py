class Solution:
    def generateKey(self, num1: int, num2: int, num3: int) -> int:
        result = [0] * 4
        for i in range(4):
            d = min(num1 % 10, num2 % 10, num3 % 10)
            num1 //= 10
            num2 //= 10
            num3 //= 10
            result[i] = d
        result.reverse()
        ans = 0
        for i in range(4):
            ans *= 10
            ans += result[i]
        return ans
