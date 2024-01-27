class Solution:
    def maxTaxiEarnings(self, n: int, rides: List[List[int]]) -> int:
        self.buckets = [[] for _ in range(n + 1)]
        for ride in rides:
            self.buckets[ride[0]].append((ride[1], ride[1] - ride[0] + ride[2]))
        self.n = n

        return self.solve(1)

    @lru_cache(int(2e5))
    def solve(self, i: int) -> int:
        if i == self.n:
            return 0

        ans = 0
        for e, t in self.buckets[i]:
            ans = max(ans, t + self.solve(e))
        ans = max(ans, self.solve(i + 1))

        return ans
