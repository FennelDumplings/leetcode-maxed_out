class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return 0
        if(self.check_right(0, nums)):
            return 0
        if(self.check_left(n - 1, nums)):
            return n - 1
        left, right = 1, n - 2
        while left <= right:
            mid = (left + right) // 2
            if self.check_left(mid, nums):
                if self.check_right(mid, nums):
                    return mid
                else:
                    left = mid + 1
            else:
                right = mid - 1
        return -1

    def check_left(self, index, nums):
        return nums[index - 1] < nums[index]

    def check_right(self, index, nums):
        return nums[index + 1] < nums[index]

