class Solution:
    def findKthSmallest(self, coins: List[int], k: int) -> int:
        n = len(coins)
        subset_lcm  = [1] * (2 ** n)
        for i in range(n):
            for j in range(1 << i):
                subset_lcm[j | (1 << i)] = math.lcm(subset_lcm[j], coins[i])

        def check(m):
            ans = 0
            for x in range(1, 1 << n):
                t = x.bit_count()
                if t % 2 == 1:
                    ans += m // subset_lcm[x]
                else:
                    ans -= m // subset_lcm[x]
            return ans

        left = k - 1
        right = min(coins) * k

        while left < right:
            mid = (left + right) // 2
            a = check(mid)
            if a < k:
                left = mid + 1
            else:
                right = mid

        return left
