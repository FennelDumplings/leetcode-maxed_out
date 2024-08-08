def trend(A, i):
    if A[i + 1] > A[i]:
        return 1
    elif A[i + 1] == A[i]:
        return 0
    else:
        return -1

class Solution:
    def temperatureTrend(self, temperatureA: List[int], temperatureB: List[int]) -> int:
        n = len(temperatureA)
        ans = 0
        l = 0
        while l < n - 1:
            r = l
            while r < n - 1 and trend(temperatureA, r) == trend(temperatureB, r):
                r += 1
            ans = max(ans, r - l)
            l = r + 1
        return ans


