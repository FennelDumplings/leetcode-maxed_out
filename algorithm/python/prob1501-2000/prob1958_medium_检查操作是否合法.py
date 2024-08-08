class Solution:
    def checkMove(self, board: List[List[str]], r: int, c: int, color: str) -> bool:
        def check(l, r, x):
            return l <= x and x <= r

        m = len(board)
        n = len(board[0])
        if board[r][c] != ".":
            return False
        dx = [0, 0, 1, 1, 1, -1, -1, -1]
        dy = [1, -1, 1, 0, -1, 1, 0, -1]
        for d in range(8):
            # 沿着方向 [dx, dy] 至少能走两步
            # 0 <= r + 2 * dx < m,
            # 0 <= c + 2 * dy < n
            if not check(0, m - 1, r + 2 * dx[d]):
                continue
            if not check(0, n - 1, c + 2 * dy[d]):
                continue
            # board[r+dx][c+dy] 必须与 color 不一样
            if board[r + dx[d]][c + dy[d]] == color or board[r + dx[d]][c + dy[d]] == ".":
                continue
            # [dx, dy] 耗尽之前至少一个与 color 一样
            k = 2
            while True:
                if not check(0, m - 1, r + k * dx[d]):
                    break
                if not check(0, n - 1, c + k * dy[d]):
                    break
                if board[r + k * dx[d]][c + k * dy[d]] == ".":
                    break
                if board[r + k * dx[d]][c + k * dy[d]] == color:
                    return True
                k += 1
        return False
