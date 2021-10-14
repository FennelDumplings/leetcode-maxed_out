
class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        # 数值范围 [−2^31,  2^31 − 1] 结果溢出则返回 2^31-1
        self.INT_MIN = -(2 ** 31)
        self.INT_MAX = 2 ** 31 - 1
        if dividend == 0:
            return 0
        if divisor == self.INT_MIN:
            if dividend == self.INT_MIN:
                return 1
            else:
                return 0
        if dividend == self.INT_MIN:
            if divisor > 0:
                return -1 - self._divide(-(dividend + divisor), divisor)
            elif divisor == -1: # 结果溢出
                return self.INT_MAX
            else:
                return 1 + self._divide(-(dividend - divisor), -divisor)
        # [-(2^31 - 1) .. 0 .. 2^31 - 1]
        if dividend < 0 and divisor < 0:
            return self._divide(-dividend, -divisor)
        elif dividend > 0 and divisor < 0:
            return -self._divide(dividend, -divisor)
        elif dividend < 0 and divisor > 0:
            return -self._divide(-dividend, divisor)
        else:
            return self._divide(dividend, divisor)

    def _divide(self, dividend: int, divisor: int) -> int:
        if dividend < divisor:
            return 0

        res = 0
        div = divisor
        i = 1
        dividend -= div
        res += i
        while dividend >= div and self.INT_MAX - div >= div and dividend > (div << 1):
            div = div << 1
            i = i << 1
            dividend -= div
            res += i
        while div > 0:
            while dividend - div >= 0:
                res += i
                dividend -= div
            div = div >> 1
            i = i >> 1
        return res
