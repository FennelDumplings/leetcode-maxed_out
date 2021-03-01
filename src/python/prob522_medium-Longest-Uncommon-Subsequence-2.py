
class Solution:
    def findLUSlength(self, strs: List[str]) -> int:
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

        ans = -1
        for i in range(len(strs)):
            flag = True
            for j in range(len(strs)):
                if i == j:
                    continue
                if check(strs[i], strs[j]):
                    flag = False
                    break
            if flag:
                ans = max(ans, len(strs[i]))

        return ans

