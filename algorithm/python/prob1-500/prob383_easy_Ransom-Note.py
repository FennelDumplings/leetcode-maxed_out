from collections import Counter

class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        counter1 = Counter(magazine)
        counter2 = Counter(ransomNote)
        for ch in counter2:
            if counter1[ch] < counter2[ch]:
                return False
        return True

