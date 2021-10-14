class Solution:
    def sumZero(self, n: int) -> List[int]:
        result = [0] * n
        for i in range(n // 2):
            result[i * 2] = i + 1
            result[i * 2 + 1] = -(i + 1)
        return result
