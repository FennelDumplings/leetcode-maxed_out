class Solution:
    def countPairs(self, nums: List[int], target: int) -> int:
        n = len(nums)
        nums.sort()
        ans = 0
        i = 0
        print(nums)
        while i < n - 1:
            x = target - nums[i]
            # nums[i+1..n-1] 找大于等于 x 的最小值
            k = bisect_left(nums, x)
            if k <= i:
                i += 1
                continue
            ans += k - i - 1
            i += 1
        return ans
