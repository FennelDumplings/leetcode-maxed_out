def quick_pow(a: int, b: int, MOD: int) -> int:
    ans = 1
    while b:
        if b & 1:
            ans = (ans * a) % MOD
        a = (a * a) % MOD
        b >>= 1
    return ans % MOD

class Solution:
    def getGoodIndices(self, variables: List[List[int]], target: int) -> List[int]:
        result = []
        for i, [a, b, c, m] in enumerate(variables):
            if quick_pow(quick_pow(a, b, 10), c, m) == target:
                result.append(i)
        return result
