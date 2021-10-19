class Solution:
    def arrayStringsAreEqual(self, word1: List[str], word2: List[str]) -> bool:
        i1 = j1 = i2 = j2 = 0
        n1 = len(word1)
        n2 = len(word2)
        while i1 < n1 and i2 < n2:
            ch1 = word1[i1][j1]
            ch2 = word2[i2][j2]
            if ch1 != ch2:
                return False
            j1 += 1
            if j1 == len(word1[i1]):
                i1 += 1
                j1 = 0
            j2 += 1
            if j2 == len(word2[i2]):
                i2 += 1
                j2 = 0
        return i1 == n1 and i2 == n2
