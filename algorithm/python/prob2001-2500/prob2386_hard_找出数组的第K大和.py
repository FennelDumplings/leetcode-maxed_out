
class Solution:
    def kSum(self, nums: List[int], k: int) -> int:
        self.n = len(nums)
        self.nums = sorted(nums)
        self.max_sums = [0] * (self.n + 1)
        for i in range(1, self.n + 1):
            self.max_sums[i] = self.max_sums[i - 1]
            if self.nums[i - 1] > 0:
                self.max_sums[i] += self.nums[i - 1]

        left = int(-2e14)
        right = int(2e14)
        while left < right:
            mid = (left + right + 1) // 2
            if self.check(mid, k):
                # nums[0..n-1] 中，和大于等于 mid 的个数小于 k
                right = mid - 1
            else:
                left = mid
        return left

    def check(self, mid, k):
        # nums[0..n-1] 中，和大于等于 mid 的个数小于 k
        cnt, flag = self.solve(self.n - 1, mid, k)
        return flag

    @functools.lru_cache()
    def solve(self, i: int, s: int, k: int):
        # nums[0..i] 中，和大于等于 s 的子序列的个数
        if self.max_sums[i + 1] < s:
            return 0, True
        if i == -1:
            if s <= 0:
                return 1, True
            else:
                return 0, True
        cnt1, flag1 = self.solve(i - 1, s - self.nums[i], k)
        if not flag1:
            return [-1, False]
        cnt2, flag2 = self.solve(i - 1, s, k)
        if not flag2:
            return [-1, False]
        cnt = cnt1 + cnt2
        return [cnt, cnt < k]
