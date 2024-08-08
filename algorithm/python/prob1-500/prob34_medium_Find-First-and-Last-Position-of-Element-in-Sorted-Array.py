import numpy as np

class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        ans = [-1, -1]
        arr = np.array(nums, dtype=np.int32)
        l = arr.searchsorted(target)
        r = arr.searchsorted(target + 1)
        if l < r:
            ans[0] = int(l)
            ans[1] = int(r) - 1
        return ans
