class Solution:
    def decrypt(self, code: List[int], k: int) -> List[int]:
        n = len(code)
        if k == 0:
            return [0] * n
        sums = [0] * n # sums[i] := [i + 1, ..., i + k] 的和
        K = abs(k)
        for i in range(K):
            sums[0] += code[(i + 1) % n]
        for i in range(1, n):
            # 求 sums[i]
            sums[i] = sums[(i + n - 1) % n] - code[i] + code[(i + K) % n]
        if k > 0:
            return sums
        else:
            right_shift = -(k - 1)
            return sums[-right_shift:] + sums[:-right_shift]
