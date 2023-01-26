class Solution:
    def countEven(self, num: int) -> int:
        ans = 0
        for x in range(1, num + 1):
            if self.check(x):
                ans += 1
        return ans

    def check(self, x):
        sum_ = 0
        while x > 0:
            sum_ += (x % 10)
            x //= 10
        return sum_ % 2 == 0

