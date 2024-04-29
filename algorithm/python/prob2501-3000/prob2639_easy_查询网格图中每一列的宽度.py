import math

class Solution:
    def findColumnWidth(self, grid: List[List[int]]) -> List[int]:

        def get_len(x):
            if x < 0:
                return 1 + get_len(-x)
            if x == 0:
                return 1
            return int(math.log10(x)) + 1

        n = len(grid)
        m = len(grid[0])
        result = [0] * m
        for j in range(m):
            w = 0
            for i in range(n):
                w = max(w, get_len(grid[i][j]))
            result[j] = w
        return result
