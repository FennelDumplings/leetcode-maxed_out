class Solution:
    def oddString(self, words: List[str]) -> str:
        counter = Counter()
        mapping = {}
        for word in words:
            diff = get_diff(word)
            counter[diff] += 1
            mapping[diff] = word
        for diff in counter:
            if counter[diff] == 1:
                return mapping[diff]
        return ""

def get_diff(word):
    n = len(word)
    result = list(range(n - 1))
    for i in range(n - 1):
        result[i] = ord(word[i + 1]) - ord(word[i])
    return tuple(result)
