class Solution:
    def countHomogenous(self, s: str) -> int:
        n = len(s)
        left = 0
        MOD = int(1e9) + 7
        ans = 0
        while left < n:
            ch = s[left]
            right = left
            while right < n and s[right] == ch:
                right += 1
            l = right - left
            ans = (ans + (1 + l) * l // 2) % MOD
            left = right
        return ans
