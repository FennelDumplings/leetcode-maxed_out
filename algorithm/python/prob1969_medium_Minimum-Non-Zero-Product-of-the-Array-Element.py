MOD = int(1e9 + 7)

def quickpower2(a, n, m):
    ans = 1
    while n > 0:
        if n % 2 == 1:
            ans = (ans * a) % m
        a = a * a % m
        n = n // 2
    return ans % m;

class Solution:
    def minNonZeroProduct(self, p: int) -> int:
        a = 2 ** p - 1
        b = a - 1
        n = (a - 1) // 2
        ans = (a * quickpower2(b, n, MOD)) % MOD
        return ans
