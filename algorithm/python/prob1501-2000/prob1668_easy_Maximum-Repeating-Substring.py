class Solution:
    def maxRepeating(self, sequence: str, word: str) -> int:
        n = len(sequence)
        m = len(word)
        right = n // m
        left = 0
        while left < right:
            mid = (left + right + 1) // 2
            if sequence.find(word * mid) != -1:
                left = mid
            else:
                right = mid - 1
        return left
