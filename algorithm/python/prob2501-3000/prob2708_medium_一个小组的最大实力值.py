import bisect

class Solution:
    def maxStrength(self, nums: List[int]) -> int:
        cnt = 0
        total = 1
        has_zero = False
        max_nega = -int(1e9)
        for x in nums:
            if x == 0:
                has_zero = True
            else:
                cnt += 1
                total *= x
                if x < 0:
                    max_nega = max(max_nega, x)
        if cnt == 0:
            return 0
        if total > 0:
            return total
        # total < 0
        if cnt == 1:
            if has_zero:
                return 0
            else:
                return total
        return total // max_nega
