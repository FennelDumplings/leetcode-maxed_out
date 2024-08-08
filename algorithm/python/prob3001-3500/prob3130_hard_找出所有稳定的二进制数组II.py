from math import comb

MOD = int(1e9 + 7)

class Solution:
    def numberOfStableArrays(self, zero: int, one: int, limit: int) -> int:
        n = zero + one
        limit += 1
        ans = comb(n, zero)
        if zero >= limit:
            ans = ans - comb(n - limit, one)
            if one >= 1:
                ans = ans - (n - limit) * comb(n - limit, one - 1)
        if one >= limit:
            ans = ans - comb(n - limit, zero)
            if zero >= 1:
                ans = ans - (n - limit) * comb(n - limit, zero - 1)
        return ans % MOD
