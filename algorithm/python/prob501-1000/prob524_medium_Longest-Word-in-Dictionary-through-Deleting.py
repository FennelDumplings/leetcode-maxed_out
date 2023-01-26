from functools import cmp_to_key

class Cmp:
    def __call__(self, word1, word2):
        # 如果 word1 < word2 则返回 True
        # 此函数定义什么叫 word1 < word2
        if len(word1) == len(word2):
            if word1 < word2:
                return -1
            elif word1 > word2:
                return 1
            else:
                return 0
        if len(word1) > len(word2):
            return -1
        elif len(word1) < len(word2):
            return 1
        else:
            return 0

class Solution:
    def findLongestWord(self, s: str, dictionary: List[str]) -> str:
        if len(s) == 0 or len(dictionary) == 0:
            return ""
        mycmp = Cmp()
        dictionary.sort(key=cmp_to_key(mycmp))
        for word in dictionary:
            if self.check(s, word):
                return word
        return ""

    def check(self, s, word):
        # 判断 word 是否是 s 的子序列
        # 这里的算法用双串单向双指针
        n = len(s)
        m = len(word)
        if m > n:
            return False
        i, j = 0, 0
        while i < n and j < m:
            if s[i] == word[j]:
                j += 1
            i += 1
            if m - j > n - i:
                return False
        return j == m
