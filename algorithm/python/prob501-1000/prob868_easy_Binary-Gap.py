class Solution:
    def binaryGap(self, n: int) -> int:
        max_gap = 0
        left = right = -1
        i = 0
        while n > 0 and n & 1 == 0:
            n >>= 1
            i += 1
        left = i
        while n > 0:
            if n & 1:
                max_gap = max(max_gap, i - left)
                left = i
            n >>= 1
            i += 1
        return max_gap
