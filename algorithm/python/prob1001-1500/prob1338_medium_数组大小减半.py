from collections import Counter

class Solution:
    def minSetSize(self, arr: List[int]) -> int:
        # 算频数
        freqs = Counter(arr)

        # 对 cnts 中的频数字段计数排序
        n = len(arr)
        freq_cnts = [0] * (n + 1)
        for x, freq in freqs.items():
            freq_cnts[freq] += 1

        # 统计结果
        s = 0
        ans = 0
        for freq in range(len(freq_cnts) - 1, -1, -1):
            cnt = freq_cnts[freq]
            if cnt == 0:
                continue
            for _ in range(cnt):
                s += freq
                ans += 1
                if s >= n // 2:
                    return ans
        return -1

