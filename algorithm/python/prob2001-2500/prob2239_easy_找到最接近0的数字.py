from functools import reduce

class Solution:
    def findClosestNumber(self, nums: List[int]) -> int:
        def reducer(x: int, y: int) -> int:
            x_abs = abs(x)
            y_abs = abs(y)
            if x_abs == y_abs:
                return max(x, y)
            elif x_abs < y_abs:
                return x
            else:
                return y
        return reduce(reducer, nums)

