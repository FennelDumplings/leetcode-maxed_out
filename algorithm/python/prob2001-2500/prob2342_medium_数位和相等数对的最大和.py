class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        # mapping[s] = [x1, x2]
        # 数位和为 s，最大的两个数为 x1, x2
        mapping = dict()
        for i in range(n):
            x = nums[i]
            s = 0
            while x > 0:
                s += x % 10;
                x //= 10
            if s in mapping:
                if nums[i] > mapping[s][0]:
                    mapping[s][1] = mapping[s][0]
                    mapping[s][0] = nums[i]
                else:
                    mapping[s][1] = max(mapping[s][1], nums[i])
            else:
                mapping[s] = [nums[i], -1]
        ans = -1
        for v in mapping.values():
            if v[1] == -1:
                continue
            ans = max(ans, v[0] + v[1])
        return ans
