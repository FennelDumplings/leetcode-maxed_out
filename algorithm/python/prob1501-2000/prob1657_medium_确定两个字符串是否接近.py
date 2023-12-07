class Solution:
    def closeStrings(self, word1: str, word2: str) -> bool:
        n1 = len(word1)
        n2 = len(word2)
        if(n1 != n2):
            return False
        counter1 = Counter(word1)
        counter2 = Counter(word2)
        key1 = sorted(counter1.keys())
        key2 = sorted(counter2.keys())
        value1 = sorted(counter1.values())
        value2 = sorted(counter2.values())
        return key1 == key2 and value1 == value2

