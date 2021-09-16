class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        mapping = {}
        for i, num in enumerate(nums):
            gap = target - num
            if gap in mapping:
                return [i, mapping[gap]]
            mapping[num] = i

