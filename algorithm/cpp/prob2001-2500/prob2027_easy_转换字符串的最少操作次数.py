class Solution:
    def minimumMoves(self, s: str) -> int:
        n = len(s)
        i = 0
        ans = 0
        while i < n - 3:
            if s[i] == "O":
                i += 1
            else:
                ans += 1
                i += 3
        while i < n:
            if s[i] == "X":
                ans += 1
                break
            i += 1
        return ans
