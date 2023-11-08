class Solution:
    def vowelStrings(self, words: List[str], left: int, right: int) -> int:
        setting = set("aeiou")
        ans = 0
        for i in range(left, right + 1):
            w = words[i]
            if w[0] in setting and w[-1] in setting:
                ans += 1
        return ans
