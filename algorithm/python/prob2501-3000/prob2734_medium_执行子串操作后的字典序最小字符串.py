class Solution:
    def smallestString(self, s: str) -> str:
        n = len(s)
        result = list(s)
        l = 0
        while l < n and s[l] == 'a':
            # 前缀的 a 跳过
            l += 1
        if l == n:
            # 全是 a
            result[-1] = chr(((ord(result[-1]) - ord('a')) - 1 + 26) % 26 + ord('a'))
        else:
            # result[l] 不是 a
            r = l + 1
            while r < n and s[r] != 'a':
                r += 1
            for i in range(l, r):
                result[i] = chr(((ord(result[i]) - ord('a')) - 1 + 26) % 26 + ord('a'))
        return "".join(result)
