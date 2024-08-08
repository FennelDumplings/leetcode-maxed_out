class Solution:
    def findIndices(self, nums: List[int], indexDifference: int, valueDifference: int) -> List[int]:
        n = len(nums)
        if indexDifference > n - 1:
            return [-1, -1]

        left_min = nums[0]
        left_min_idx = 0
        left_max = nums[0]
        left_max_idx = 0
        for j in range(indexDifference, n):
            if nums[j] - left_min >= valueDifference:
                return [left_min_idx, j]
            if left_max - nums[j] >= valueDifference:
                return [left_max_idx, j]

            i = j - indexDifference + 1
            if nums[i] < left_min:
                left_min = nums[i]
                left_min_idx = i
            if nums[i] > left_max:
                left_max = nums[i]
                left_max_idx = i

        return [-1, -1]
