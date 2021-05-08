class Key:
    def __init__(self, nums):
        self.nums = nums

    def __call__(self, i):
        return self.nums[i]


class Solution:
    def findRelativeRanks(self, nums: List[int]) -> List[str]:
        n = len(nums)
        indexes = [i for i in range(n)]
        mykey = Key(nums)
        indexes.sort(key=mykey, reverse=True)
        result = ["" for _ in range(n)]
        for i, idx in enumerate(indexes):
            if i == 0:
                result[idx] = "Gold Medal"
            elif i == 1:
                result[idx] = "Silver Medal"
            elif i == 2:
                result[idx] = "Bronze Medal"
            else:
                result[idx] = str(i + 1)
        return result
