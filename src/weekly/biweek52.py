class Solution:
    def sortSentence(self, s: str) -> str:
        words = s.split(" ")
        n = len(words)
        strs = [""] * n
        for word in words:
            x = word[:-1]
            idx = int(word[-1])
            strs[idx - 1] = x
        return " ".join(strs)
