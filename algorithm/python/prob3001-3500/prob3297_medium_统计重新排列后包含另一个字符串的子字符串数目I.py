from collections import Counter

def contain(cnt, cnt2):
    # 判断 cnt 是否包含了 cnt2
    return all(cnt[c] >= cnt2[c] for c in cnt2)

class Solution:
    def validSubstringCount(self, word1: str, word2: str) -> int:
        n1 = len(word1)
        n2 = len(word2)
        cnt2 = Counter(word2)
        l = 0
        r = -1
        cnt = Counter()
        ans = 0
        while l < n1 and r < n1:
            while not contain(cnt, cnt2):
                r += 1
                if r >= n1:
                    break
                cnt[word1[r]] += 1
            if r < n1:
                ans += n1 - r
            cnt[word1[l]] -= 1
            l += 1
        return ans
