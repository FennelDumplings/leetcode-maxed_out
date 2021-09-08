class Solution:
    def numOfStrings(self, patterns: List[str], word: str) -> int:
        ans = 0
        for s in patterns:
            if s in word:
                ans += 1
        return ans
