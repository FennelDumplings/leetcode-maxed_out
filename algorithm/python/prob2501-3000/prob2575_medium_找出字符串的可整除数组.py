class Solution:
    def divisibilityArray(self, word: str, m: int) -> List[int]:
        n = len(word)
        # pre_mods[i] := int(word[0..i-1]) mod m
        # pre_mods[i] = (pre_mods[i - 1] * 10 + word[i - 1]) % m
        pre_mods = 0
        result = [0] * n
        for i in range(n):
            pre_mods = (pre_mods * 10 + int(word[i])) % m
            if pre_mods == 0:
                result[i] = 1
        return result
