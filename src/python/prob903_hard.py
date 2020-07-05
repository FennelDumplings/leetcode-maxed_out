# https://leetcode-cn.com/problems/valid-permutations-for-di-sequence/solution/chao-xiang-xi-fen-zhi-fa-si-lu-ma-ma-zai-ye-bu-yon/
# 分治法+区间DP 的解法

from functools import lru_cache

class Solution:
    def numPermsDISequence(self, S):
        MOD = 10**9 + 7

        @lru_cache(None)
        def factorial(n):
            if n == 1:
                return 1
            return factorial(n - 1) * n

        @lru_cache(None)
        def getPermsDISeq(i, j, S):
            res = 0
            if i >= j:
                return 1


            if S[i] == 'I':
                res += getPermsDISeq(i + 1, j, S) % MOD

            if S[j] == 'D':
                res += getPermsDISeq(i, j - 1, S) % MOD

            for k in range(i, j):
                if S[k] == 'D' and S[k + 1] == 'I':
                    res += getPermsDISeq(i, k - 1, S) * getPermsDISeq(k + 2, j, S) * factorial(j - i + 1) // factorial(k - i + 1) // factorial(j - k) % MOD

            return res % MOD
        return getPermsDISeq(0, len(S) - 1, S)

