import numpy as np

def block_id(i, j):
    r = i // 3
    c = j // 3
    return 3 * r + c

class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        row_state = np.array([False] * 9 * 9, np.bool_).reshape(9, 9)
        col_state = np.array([False] * 9 * 9, np.bool_).reshape(9, 9)
        block_state = np.array([False] * 9 * 9, np.bool_).reshape(9, 9)
        for i in range(9):
            for j in range(9):
                if board[i][j] != ".":
                    num = int(board[i][j])
                    if row_state[i][num - 1]:
                        return False
                    row_state[i][num - 1] = True
                    if col_state[j][num - 1]:
                        return False
                    col_state[j][num - 1] = True
                    if block_state[block_id(i, j)][num - 1]:
                        return False
                    block_state[block_id(i, j)][num - 1] = True
        return True
