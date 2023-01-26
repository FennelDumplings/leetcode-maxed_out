class Solution:
    def maxCount(self, m: int, n: int, ops: List[List[int]]) -> int:
        if len(ops) == 0:
            return n * m
        x = min((i[0] for i in ops))
        y = min((i[1] for i in ops))
        return x * y
