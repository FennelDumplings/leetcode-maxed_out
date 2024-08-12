class Solution:
    def minimumAddedInteger(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums2)
        nums1.sort()
        nums2.sort()
        # 与 nums2[0] 对应的只可能是 nums1[l], l = 0, 1, 2
        # x = nums2[0] - nums1[l]，l 越大，x 越小

        def process(l: int) -> bool:
            # 0 <= l <= 2
            x = nums2[0] - nums1[l]
            c = 2 - l # nums1 可跳过 c 个
            i1 = l + 1
            i2 = 1
            while i2 < n:
                if nums2[i2] - nums1[i1] != x:
                    if c > 0:
                        c -= 1
                    else:
                        return False
                else:
                    i2 += 1
                i1 += 1
            return True

        for l in [2, 1, 0]:
            if process(l):
                return nums2[0] - nums1[l]

        return int(2e9)
