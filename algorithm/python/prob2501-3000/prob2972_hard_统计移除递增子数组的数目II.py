class Solution:
    def incremovableSubarrayCount(self, nums: List[int]) -> int:
        n = len(nums)
        l = 0
        while l + 1 < n and nums[l] < nums[l + 1]:
            l += 1
        if l == n - 1:
            return n * (n + 1) // 2
        r = n - 1
        while l < r - 1 and nums[r - 1] < nums[r]:
            r -= 1
        print(l, r)
        ans = 1 + n - r # 以 0 开始的子数组个数
        print(ans)
        i = 0
        j = r
        while i <= l:
            while j < n and nums[i] >= nums[j]:
                j += 1
            # 以 i + 1 开头的子数组个数
            ans += 1 + n - j
            i += 1
        return ans
