from collections import Counter

class Solution:
    def validSubstringCount(self, word1: str, word2: str) -> int:
        n1 = len(word1)
        n2 = len(word2)
        cnt2 = Counter(word2)
        s = len(cnt2)
        l = 0
        r = -1
        cnt = Counter()
        ans = 0
        while l < n1 and r < n1:
            while s > 0:
                r += 1
                if r >= n1:
                    break
                cnt[word1[r]] += 1
                # 维护增加的聚合信息 s
                if cnt2[word1[r]] - cnt[word1[r]] == 0:
                    s -= 1

            if r < n1:
                ans += n1 - r
            cnt[word1[l]] -= 1
            # 维护增加的聚合信息 s
            if cnt2[word1[l]] - cnt[word1[l]] > 0:
                s += 1
            l += 1
        return ans
