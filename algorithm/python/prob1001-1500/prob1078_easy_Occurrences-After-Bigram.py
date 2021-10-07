class Solution:
    def findOcurrences(self, text: str, first: str, second: str) -> List[str]:
        words = text.split(" ")
        n = len(words)
        result = []
        for i in range(n - 2):
            if words[i] == first and words[i + 1] == second:
                result.append(words[i + 2])
        return result
