class Solution:
    def diStringMatch(self, s: str) -> List[int]:
        N = len(s)
        delta = 0
        sums = [(0, 0)] * (N + 1)
        for i, x in enumerate(s):
            if x == "I":
                delta += 1
            else:
                delta -= 1
            sums[i + 1] = (delta, i + 1)
        sums.sort()
        result = [0] * (N + 1)
        for i in range(N + 1):
            result[sums[i][1]] = i
        return result


