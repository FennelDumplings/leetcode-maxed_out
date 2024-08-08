class Solution:
    def findIntersectionValues(self, nums1: List[int], nums2: List[int]) -> List[int]:
        counter1 = Counter(nums1)
        counter2 = Counter(nums2)
        result = [0, 0]
        for x in nums1:
            if x in counter2:
                result[0] += 1
        for x in nums2:
            if x in counter1:
                result[1] += 1
        return result
