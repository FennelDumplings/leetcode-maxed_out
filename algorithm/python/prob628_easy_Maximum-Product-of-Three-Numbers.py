class Solution:
    def maximumProduct(self, nums: List[int]) -> int:
        if len(nums) == 3:
            return nums[0] * nums[1] * nums[2]
        ans = nums[0] * nums[1] * nums[2]

        # max1 < max2 < max3
        # min1 < min2
        max1 = min(nums[:3])
        max3 = max(nums[:3])
        max2 = sum(nums[:3]) - (max1 + max3)
        min1 = max1
        min2 = max2

        def update(max1, max2, max3, min1, min2, x):
            if x > max3:
                max1 = max2
                max2 = max3
                max3 = x
            elif x > max2:
                max1 = max2
                max2 = x
            elif x > max1:
                max1 = x
            if x < min1:
                min2 = min1
                min1 = x
            elif x < min2:
                min2 = x
            return max1, max2, max3, min1, min2

        for i in range(3, len(nums)):
            max1, max2, max3, min1, min2 = update(max1, max2, max3, min1, min2, nums[i])
            ans = max(ans, max1 * max2 * max3)
            ans = max(ans, min1 * min2 * max3)

        return ans
