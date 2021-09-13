class Solution:
    def shortestToChar(self, S: str, C: str) -> List[int]:
        n = len(S)
        idxs = []
        for i in range(n):
            if C == S[i]:
                idxs.append(i)
        result = [0] * n
        for i in range(idxs[0]):
            result[i] = idxs[0] - i
        for i in range(idxs[-1] + 1, n):
            result[i] = i - idxs[-1]
        m = len(idxs)
        if m == 1:
            return result
        for i in range(1, m):
            r = idxs[i]
            l = idxs[i - 1]
            for j in range(l + 1, r):
                result[j] = min(j - l, r - j)
        return result
