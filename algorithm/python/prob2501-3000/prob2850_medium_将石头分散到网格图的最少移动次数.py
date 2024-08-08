from itertools import permutations

def dist(s: int, t: int) -> int:
    return abs(s[0] - t[0]) + abs(s[1] - t[1])

INF = int(1e9)

class Solution:
    def minimumMoves(self, grid: List[List[int]]) -> int:
        source_list = []
        target_list = []
        for i in range(3):
            for j in range(3):
                if grid[i][j] == 0:
                    target_list.append((i, j))
                elif grid[i][j] > 1:
                    source_list.extend([(i, j)] * (grid[i][j] - 1))

        n = len(source_list)
        if n == 0:
            return 0

        ans = INF
        for source_perm in permutations(source_list):
            s = 0
            for x, y in zip(source_list, target_list):
                s += dist(x, y)
            ans = min(ans, s)

        return ans
