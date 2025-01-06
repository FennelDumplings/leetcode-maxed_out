class Solution:
    def maxConsecutive(self, bottom: int, top: int, special: List[int]) -> int:
        special.extend([bottom - 1, top + 1])
        special.sort()
        n = len(special)
        ans = 0
        for i in range(n - 1):
            if special[i] < bottom - 1:
                continue
            if special[i + 1] > top + 1:
                continue
            ans = max(ans, special[i + 1] - special[i] - 1)
        return ans
