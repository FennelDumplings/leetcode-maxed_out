class Solution:
    def findKOr(self, nums: List[int], k: int) -> int:
        ans = 0
        for i in range(32):
            cnt = 0
            for x in nums:
                if (x >> i) & 1 == 1:
                    cnt += 1
            if cnt >= k:
                ans |= (1 << i)
        return ans
