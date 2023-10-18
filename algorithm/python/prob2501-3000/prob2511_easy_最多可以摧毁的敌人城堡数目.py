class Solution:
    def captureForts(self, forts: List[int]) -> int:
        n = len(forts)
        l = 0
        ans = 0
        while l < n:
            while l < n and forts[l] != 0:
                l += 1
            r = l
            while r < n and forts[r] == 0:
                r += 1
            if l - 1 >= 0 and r < n and forts[l - 1] + forts[r] == 0:
                ans = max(ans, r - l)
            l = r + 1
        return ans
