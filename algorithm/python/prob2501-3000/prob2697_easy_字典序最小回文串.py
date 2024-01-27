class Solution:
    def makeSmallestPalindrome(self, s: str) -> str:
        n = len(s)
        l = 0
        r = n - 1
        result = list(s)
        while l < r:
            if ord(s[l]) < ord(s[r]):
                result[r] = s[l]
            elif ord(s[l]) > ord(s[r]):
                result[l] = s[r]
            l += 1
            r -= 1
        return "".join(result)
