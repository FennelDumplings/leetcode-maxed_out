class Solution:
    def numberOfLines(self, widths: List[int], s: str) -> List[int]:
        n = len(widths)
        i = 0 # 行
        j = 0 # 前进单位数
        for ch in s:
            step = widths[ord(ch) - ord('a')]
            if j + step > 100:
                i += 1
                j = 0
            j += step
        return [i + 1, j]
