class Solution:
    def countAsterisks(self, s: str) -> int:
        n = len(s)
        ans = 0
        left = 0
        while left < n:
            while left < n and s[left] != "|":
                if s[left] == "*":
                    ans += 1
                left += 1
            if left == n:
                break
            right = left + 1
            while right < n and s[right] != "|":
                right += 1
            left = right + 1
        return ans
