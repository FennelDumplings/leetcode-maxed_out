class Solution:
    def minimumLevels(self, possible: List[int]) -> int:
        n = len(possible)
        S = sum(possible) # 1 的总数
        s = 0
        for i in range(n - 1):
            # Alice 玩 [0..i]
            if possible[i] == 1:
                s += 1
            if s * 2 - i - 1 > 2 * (S - s) - n + i + 1:
                return i + 1
        return -1

