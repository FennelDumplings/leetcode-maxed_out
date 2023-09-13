class Solution:
    def minNumber(self, nums1: List[int], nums2: List[int]) -> int:
        setting1 = set(nums1)
        setting2 = set(nums2)
        flag1 = False
        flag2 = False
        ans = 0
        for x in range(1, 10):
            if x in setting1 and x in setting2:
                return x
            if not flag1 and x in setting1:
                flag1 = True
                ans *= 10
                ans += x
            if not flag2 and x in setting2:
                flag2 = True
                ans *= 10
                ans += x
        return ans
