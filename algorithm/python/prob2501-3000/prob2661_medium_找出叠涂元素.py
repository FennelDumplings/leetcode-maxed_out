class Solution:
    def firstCompleteIndex(self, arr: List[int], mat: List[List[int]]) -> int:
        n = len(mat)
        m = len(mat[0])
        mapping = {} # mapping[x] -> (ix, jx)
        for i in range(n):
            for j in range(m):
                mapping[mat[i][j]] = (i, j)
        row_info = {} # row_info[row] 第 row 行已经涂色的各个列
        col_info = {} # col_info[col] 第 col 列已经涂色的各个行
        for i, x in enumerate(arr):
            row = mapping[x][0]
            col = mapping[x][1]
            if row not in row_info:
                row_info[row] = set()
            row_info[row].add(col)
            if len(row_info[row]) == m:
                return i
            if col not in col_info:
                col_info[col] = set()
            col_info[col].add(row)
            if len(col_info[col]) == n:
                return i
        return n * m
