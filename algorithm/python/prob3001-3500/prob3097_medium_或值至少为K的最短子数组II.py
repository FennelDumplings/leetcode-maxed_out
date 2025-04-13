def check(cnt, k):
    s = 0
    b = 1
    for i in range(len(cnt)):
        if cnt[i] > 0:
            s += b
        b *= 2
    return s >= k

class Solution:
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        INF = int(1e9)
        n = len(nums)
        cnt = [0] * 32
        l = 0
        r = -1
        ans = INF
        while l < n and r < n:
            while r < l or not check(cnt, k):
                r += 1
                if r == n:
                    break
                # 推进 r 后更新字符计数
                x = nums[r]
                i = 0
                while x > 0:
                    if x & 1 == 1:
                        cnt[i] += 1
                    x >>= 1
                    i += 1
            if r < n:
                ans = min(ans, r - l + 1)
            # 更新字符计数后推进 l
            y = nums[l]
            j = 0
            while y > 0:
                if y & 1 == 1:
                    cnt[j] -= 1
                y >>= 1
                j += 1
            l += 1
        return ans if ans <= n else -1
