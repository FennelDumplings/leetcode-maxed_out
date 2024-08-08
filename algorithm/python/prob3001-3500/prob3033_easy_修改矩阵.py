class Solution:
    def modifiedMatrix(self, matrix: List[List[int]]) -> List[List[int]]:
        m = len(matrix)
        n = len(matrix[1]) # 列数
        col_max = [-1] * n
        for j in range(n):
            for i in range(m):
                col_max[j] = max(col_max[j], matrix[i][j])
        answer = copy.deepcopy(matrix)
        for i in range(m):
            for j in range(n):
                if answer[i][j] == -1:
                    answer[i][j] = col_max[j]
        return answer
