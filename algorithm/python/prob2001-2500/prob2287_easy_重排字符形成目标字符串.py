class Solution:
    def rearrangeCharacters(self, s: str, target: str) -> int:
        cnt_s = Counter(s)
        cnt_target = Counter(target)
        ans = len(s)
        for ch in cnt_target:
            if ch not in cnt_s:
                return 0
            ans = min(ans, cnt_s[ch] // cnt_target[ch])
        return ans
