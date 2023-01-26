class NumMatrix:
    def __init__(self, matrix: List[List[int]]):
        n = len(matrix)
        m = len(matrix[0])
        self.sums = [[0] * (m + 1) for _ in range(n + 1)]
        for i in range(n):
            for j in range(m):
                self.sums[i + 1][j + 1] = matrix[i][j] + self.sums[i][j + 1] \
                        + self.sums[i + 1][j] - self.sums[i][j]

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return int(self.sums[row2 + 1][col2 + 1] - self.sums[row2 + 1][col1] \
                - self.sums[row1][col2 + 1] + self.sums[row1][col1])

# Your NumMatrix object will be instantiated and called as such:
# obj = NumMatrix(matrix)
# param_1 = obj.sumRegion(row1,col1,row2,col2)
