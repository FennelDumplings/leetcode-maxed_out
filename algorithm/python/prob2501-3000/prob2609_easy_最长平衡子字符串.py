class Solution:
    def findTheLongestBalancedSubstring(self, s: str) -> int:
        n = len(s)
        ans = 0
        l = 0
        while l < n:
            n0 = n1 = 0
            r = l
            while r < n and s[r] == "0":
                r += 1
            n0 = r - l
            while r < n and s[r] == "1":
                r += 1
            n1 = r - l - n0
            ans = max(ans, 2 * min(n0, n1))
            l = r
        return ans
