class Solution:
    def evaluate(self, s: str, knowledge: List[List[str]]) -> str:
        mapping = {}
        for k, v in knowledge:
            mapping[k] = v
        result = []
        n = len(s)
        i = 0
        while i < n:
            j = i
            while j < n and s[j] != '(':
                j += 1
            result.append(s[i:j])
            if j < n:
                j += 1
                i = j
                while j < n and s[j] != ")":
                    j += 1
                word = s[i:j]
                if word in mapping:
                    result.append(mapping[word])
                else:
                    result.append("?")
                j += 1
            i = j
        return "".join(result)
