class Solution:
    def largestCombination(self, candidates: List[int]) -> int:
        a = [0] * 32
        for x in candidates:
            i = 0
            while x > 0:
                if (x & 1) == 1:
                    a[i] += 1
                x >>= 1
                i += 1
        return max(a)

