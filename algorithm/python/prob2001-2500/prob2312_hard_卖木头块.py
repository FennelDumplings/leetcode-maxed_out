class Solution:
    def sellingWood(self, m: int, n: int, prices: List[List[int]]) -> int:
        self.p = [[0 for _ in range(n + 1)] for _ in range(m + 1)]
        for i, j, price in prices:
            self.p[i][j] = price
        return self.solve(m, n)

   @functools.lru_cache(int(1e8))
    def solve(self, i: int, j: int) -> int:
        ans = self.p[i][j]
        for h in range(1, i // 2 + 1):
            ans = max(ans, self.solve(h, j) + self.solve(i - h, j))
        for w in range(1, j // 2 + 1):
            ans = max(ans, self.solve(i, w) + self.solve(i, j - w))
        return ans
