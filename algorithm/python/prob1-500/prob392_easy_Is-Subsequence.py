class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        # 判断 s 是否是 t 的子序列
        # 这里的算法用双串单向双指针
        m = len(s)
        n = len(t)
        if m > n:
            return False
        i, j = 0, 0
        while i < n and j < m:
            if t[i] == s[j]:
                j += 1
            i += 1
            if m - j > n - i:
                return False
        return j == m
