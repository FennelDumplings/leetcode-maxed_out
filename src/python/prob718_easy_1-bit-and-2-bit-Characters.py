class Solution:
    def isOneBitCharacter(self, bits: List[int]) -> bool:
        i = len(bits) - 2
        while i >= 0 and bits[i] == 1:
            i -= 1
        return ((len(bits) - 1 - i) & 1) == 1

