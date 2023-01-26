class NumArray:
    def __init__(self, nums: List[int]):
        n = len(nums)
        self.sums = [0] * (n + 1)
        for i in range(n):
            self.sums [i + 1] = self.sums[i] + nums[i]

    def sumRange(self, left: int, right: int) -> int:
        return self.sums[right + 1] - self.sums[left]

# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# param_1 = obj.sumRange(left,right)
