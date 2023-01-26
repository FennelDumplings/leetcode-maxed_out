import numpy as np

def block_id(i, j):
    r = i // 3
    c = j // 3
    return 3 * r + c

class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        self.row_state = np.array([False] * 9 * 9, np.bool_).reshape(9, 9)
        self.col_state = np.array([False] * 9 * 9, np.bool_).reshape(9, 9)
        self.block_state = np.array([False] * 9 * 9, np.bool_).reshape(9, 9)
        for i in range(9):
            for j in range(9):
                if board[i][j] != ".":
                    num = int(board[i][j])
                    self.row_state[i][num - 1] = True
                    self.col_state[j][num - 1] = True
                    self.block_state[block_id(i, j)][num - 1] = True
        return self.dfs(board, 0, 0)

    def dfs(self, board, i, j):
        if i == 9:
            return True
        nxt_i = (i * 9 + j + 1) // 9
        nxt_j = (i * 9 + j + 1) % 9
        if board[i][j] != ".":
            return self.dfs(board, nxt_i, nxt_j)
        for num in range(1, 10):
            if self.row_state[i][num - 1]:
                continue
            if self.col_state[j][num - 1]:
                continue
            if self.block_state[block_id(i, j)][num - 1]:
                continue
            board[i][j] = str(num)
            self.row_state[i][num - 1] = True
            self.col_state[j][num - 1] = True
            self.block_state[block_id(i, j)][num - 1] = True
            if self.dfs(board, nxt_i, nxt_j):
                return True
            board[i][j] = "."
            self.row_state[i][num - 1] = False
            self.col_state[j][num - 1] = False
            self.block_state[block_id(i, j)][num - 1] = False
        return False
