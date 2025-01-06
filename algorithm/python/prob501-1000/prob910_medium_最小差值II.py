
class Solution:
    def smallestRangeII(self, A: List[int], k: int) -> int:
        A.sort()
        n = len(A)
        l, h = A[0], A[n - 1]
        d = h - l
        for i in range(n - 1):
            s, t = A[i], A[i + 1]
            d = min(d, max(s + k, h - k) - min(t - k, l + k))
        return d
