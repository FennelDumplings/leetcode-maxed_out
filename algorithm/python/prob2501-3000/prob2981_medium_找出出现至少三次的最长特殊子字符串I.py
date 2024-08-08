class Solution:
    def maximumLength(self, s: str) -> int:
        mapping = [[] for _ in range(26)]
        n = len(s)
        l = 0
        while l < n:
            ch = s[l]
            r = l + 1
            while r < n and s[r] == ch:
                r += 1
            mapping[ord(ch) - ord('a')].append(r - l)
            l = r
        ans = -1
        for i in range(26):
            if len(mapping[i]) == 0:
                continue
            if len(mapping[i]) == 1 and mapping[i][0] <= 2:
                continue
            if len(mapping[i]) == 2 and mapping[i][0] == 1 and mapping[i][1] == 1:
                continue
            max_lens = [-1] * 3
            for x in mapping[i]:
                if x >= max_lens[0]:
                    max_lens[2] = max_lens[1]
                    max_lens[1] = max_lens[0]
                    max_lens[0] = x
                elif x >= max_lens[1]:
                    max_lens[2] = max_lens[1]
                    max_lens[1] = x
                elif x >= max_lens[2]:
                    max_lens[2] = x
            if max_lens[0] == max_lens[1] and max_lens[0] == max_lens[2]:
                ans = max(ans, max_lens[0])
            elif max_lens[1] + 1 >= max_lens[0]:
                ans = max(ans, max_lens[0] - 1)
            else:
                ans = max(ans, max_lens[0] - 2)
        return ans



