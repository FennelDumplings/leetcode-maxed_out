class Solution:
    def isArraySpecial(self, nums: List[int], queries: List[List[int]]) -> List[bool]:
        n = len(nums)
        # mapping[i] := 最大的 j 使得 nums[i..j] 为特殊数组
        mapping = list(range(n))
        l = 0
        while l < n:
            prev = nums[l] & 1
            r = l + 1
            while r < n:
                cur = nums[r] & 1
                if cur == prev:
                    break
                prev = cur
                r += 1
            while l < r:
                mapping[l] = r - 1
                l += 1
        m = len(queries)
        result = [False] * m
        for i, (x, y) in enumerate(queries):
            if mapping[x] == mapping[y]:
                result[i] = True
        return result
