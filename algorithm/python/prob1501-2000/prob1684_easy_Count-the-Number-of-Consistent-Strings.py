class Solution:
    def countConsistentStrings(self, allowed: str, words: List[str]) -> int:
        setting = set(allowed)
        ans = 0
        for word in words:
            flag = True
            for ch in word:
                if ch not in setting:
                    flag = False
                    break
            if flag:
                ans += 1
        return ans
