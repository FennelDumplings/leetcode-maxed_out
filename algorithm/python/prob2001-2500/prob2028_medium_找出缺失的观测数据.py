class Solution:
    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:
        m = len(rolls)
        sm = sum(rolls)
        sn = mean * (m + n) - sm
        k = sn // n
        t = sn % n
        if k == 0 or (k == 6 and t > 0):
            return []
        result = [k + 1] * t + [k] * (n - t)
        return result
