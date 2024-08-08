from functools import lru_cache

MOD = int(1e9 + 7)

class Solution:
    def specialPerm(self, nums: List[int]) -> int:

        @lru_cache(int(1e8))
        def solve(i: int, s: int) -> int:
            s |= (1 << i)
            if s == (1 << n) - 1:
                # 当前是最后一个数
                return 1
            ans = 0
            for j in g[i]:
                # 下一个数的可能选择
                if (s >> j) & 1 == 1:
                    continue
                ans = (ans + solve(j, s)) % MOD
            return ans

        n = len(nums)
        g = [[] for _ in range(n)]
        for i in range(n - 1):
            for j in range(i + 1, n):
                if max(nums[i], nums[j]) % min(nums[i], nums[j]) == 0:
                    g[i].append(j)
                    g[j].append(i)

        ans = 0
        for i in range(n):
            ans = (ans + solve(i, 0)) % MOD
        return ans
