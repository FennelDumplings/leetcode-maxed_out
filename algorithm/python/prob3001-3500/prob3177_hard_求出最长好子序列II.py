class Solution:
    def maximumLength(self, nums: List[int], K: int) -> int:
        dp = [{} for _ in range(K + 1)]
        n = len(nums)
        mx1 = [(-1, 0) for _ in range(K + 1)]
        mx2 = [(-1, 0) for _ in range(K + 1)]
        for i in range(n):
            x = nums[i]
            for k in range(K + 1):
                if x not in dp[k]:
                    dp[k][x] = 1
                else:
                    dp[k][x] += 1
                if k > 0:
                    if mx1[k - 1][0] == x:
                        dp[k][x] = max(dp[k][x], mx2[k - 1][1] + 1)
                    else:
                        dp[k][x] = max(dp[k][x], mx1[k - 1][1] + 1)
                if dp[k][x] > mx1[k][1]:
                    mx2[k] = mx1[k]
                    mx1[k] = (x, dp[k][x])
                elif dp[k][x] > mx2[k][1]:
                    mx2[k] = (x, dp[k][x])
        ans = 0
        for x in dp[K]:
            ans = max(ans, dp[K][x])
        return ans
