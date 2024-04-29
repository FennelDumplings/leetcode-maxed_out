MOD = int(1e9 + 7)

class Solution:
    def firstDayBeenInAllRooms(self, nextVisit: List[int]) -> int:
        n = len(nextVisit)
        f = [0] * n
        g = [0] * n
        g[0] = 1
        for i in range(1, n):
            f[i] = (f[i - 1] + g[i - 1] + 1) % MOD
            g[i] = (1 + f[i] - f[nextVisit[i]]) % MOD
        return f[n - 1]
