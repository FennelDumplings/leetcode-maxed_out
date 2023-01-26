class Solution:
    def largestMerge(self, word1: str, word2: str) -> str:
        n = len(word1)
        m = len(word2)
        i = j = 0
        result = ""
        while i < n and j < m:
            if word1[i] > word2[j]:
                result += word1[i]
                i += 1
            elif word1[i] < word2[j]:
                result += word2[j]
                j += 1
            else:
                if i + 1 == n and j + 1 == m:
                    result += word1[i]
                    result += word2[j]
                    i += 1
                    j += 1
                elif i + 1 == n:
                    result += word2[j]
                    j += 1
                elif j + 1 == m:
                    result += word1[i]
                    i += 1
                else:
                    if word1[i + 1] < x and word2[j + 1] < x:
                        result += word1[i]
                        result += word2[j]
                        i += 1
                        j += 1
                    elif
        while i < n:
            result += word1[i]
        while j < m:
            result += word2[j]
        return result
