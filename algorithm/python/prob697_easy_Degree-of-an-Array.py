
class Solution:
    def findShortestSubArray(self, nums: List[int]) -> int:
        mapping = {}
        for i, x in enumerate(nums):
            if mapping.get(x, None):
                mapping[x][0] += 1
                mapping[x][1] = min(mapping[x][1], i)
                mapping[x][2] = max(mapping[x][2], i)
            else:
                mapping[x] = [1, i, i]
        max_cnt = 0
        min_len = len(nums)
        for _, v in mapping.items():
            if max_cnt < v[0]:
                max_cnt = v[0]
                min_len = v[2] - v[1] + 1
            elif max_cnt == v[0]:
                min_len = min(min_len, v[2] - v[1] + 1)
        return min_len
