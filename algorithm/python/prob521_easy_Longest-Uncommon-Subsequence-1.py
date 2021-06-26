class Solution:
    def findLUSlength(self, a: str, b: str) -> int:
        def check(p: str, s: str) -> bool:
            """
            p 是否为 s 的子序列
            """
            if len(p) > len(s):
                return False
            i = j = 0
            while i < len(s) and j < len(p):
                if p[j] == s[i]:
                    j += 1
                i += 1
            return j == len(p)

        flaga = check(a, b)
        flagb = check(b, a)
        ans = -1
        if not flaga:
            ans = max(ans, len(a))
        if not flagb:
            ans = max(ans, len(b))
        return ans

