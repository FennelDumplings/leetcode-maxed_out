MOD = int(1e9 + 7)

class Solution:
    def minimumPossibleSum(self, n: int, target: int) -> int:
        m = target // 2
        if n <= m:
            return (n * (n + 1) // 2) % MOD
        ans = m * (m + 1) // 2
        k = n - m
        if k > 0:
            ans += k * (target + (target + k - 1)) // 2
        return ans % MOD
