def get_min_representation(s: List[int]) -> int:
    N = len(s)
    i = 0
    j = 1
    while i < N and j < N:
        k = 0
        while k < N and s[(i + k) % N] == s[(j + k) % N]:
            k += 1
        if k == N:
            break
        if s[(i + k) % N] < s[(j + k) % N]:
            j += k + 1
            if i == j:
                j += 1
        else:
            i += k + 1
            if i == j:
                i += 1
    return min(i, j)

class Solution:
    def orderlyQueue(self, s: str, k: int) -> str:
        n = len(s)
        if k == 1:
            ans = get_min_representation(s)
            result = []
            for k in range(n):
                result.append(s[(ans + k) % n])
            return "".join(result)
        result = list(s)
        result.sort()
        return "".join(result)
