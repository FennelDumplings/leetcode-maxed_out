class Solution:
    def findChampion(self, grid: List[List[int]]) -> int:
        n = len(grid)
        for i in range(n):
            flag = True
            for j, x in enumerate(grid[i]):
                if i != j and x == 0:
                    # j 比 i 强
                    flag = False
                    break
            if flag:
                return i
        return -1
