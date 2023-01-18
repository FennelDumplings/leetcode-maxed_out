class Solution:
    def areSentencesSimilar(self, sentence1: str, sentence2: str) -> bool:
        words1 = sentence1.split(" ")
        words2 = sentence2.split(" ")
        n1 = len(words1)
        n2 = len(words2)
        if n1 == 1:
            return words2[0] == words1[0] or words2[n2 - 1] == words1[0]
        if n2 == 1:
            return words1[0] == words2[0] or words1[n1 - 1] == words2[0]
        l1 = 0
        r1 = n1 - 1
        l2 = 0
        r2 = n2 - 1
        while l1 < n1 and l2 < n2 and words1[l1] == words2[l2]:
            l1 += 1
            l2 += 1
        if l1 == n1 or l2 == n2:
            return True
        while l1 < r1 and l2 < r2 and words1[r1] == words2[r2]:
            r1 -= 1
            r2 -= 1
        if l1 == r1 or l2 == r2:
            return True
        return False
