class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        n = len(paragraph)
        banned_word = set(banned)
        mapping = dict()
        l = 0
        while l < n:
            r = l
            while r < n and paragraph[r].isalpha():
                r += 1
            word = paragraph[l:r].lower()
            if word not in banned_word:
                if word not in mapping:
                    mapping[word] = 0
                mapping[word] += 1
            l = r + 1
            while l < n and not paragraph[l].isalpha():
                l += 1
        max_cnt = 0
        ans = ""
        for word, cnt in mapping.items():
            if cnt > max_cnt:
                max_cnt = cnt
                ans = word
        return ans
