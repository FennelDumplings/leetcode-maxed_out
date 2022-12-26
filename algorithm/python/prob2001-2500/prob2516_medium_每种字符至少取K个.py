class Solution:
    def takeCharacters(self, s: str, k: int) -> int:
        cnts = [0, 0, 0]
        for ch in s:
            cnts[ord(ch) - ord('a')] += 1
        for cnt in cnts:
            if cnt < k:
                return -1

        def _check(_cnts):
            for i in range(3):
                if cnts[i] - k < _cnts[i]:
                    return False
            return True

        max_length = 0
        n = len(s)
        cur_cnts = [0, 0, 0]
        left = 0
        right = -1
        while left < n:
            right += 1
            while right < n:
                cur_cnts[ord(s[right]) - ord('a')] += 1
                if not _check(cur_cnts):
                    break
                right += 1
            length = right - left
            max_length = max(max_length, length)
            if right == n:
                break
            while left <= right:
                cur_cnts[ord(s[left]) - ord('a')] -= 1
                left += 1
                if _check(cur_cnts):
                    break
        return n - max_length
