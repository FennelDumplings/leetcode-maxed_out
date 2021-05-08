
import numpy as np

class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        arr = np.array(nums, dtype=np.int32)
        pos = arr.searchsorted(target)
        return int(pos)

