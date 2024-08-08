class Solution:
    def countTestedDevices(self, batteryPercentages: List[int]) -> int:
        ans = 0
        d = 0
        for i, b in enumerate(batteryPercentages):
            if b > i - d:
                ans += 1
                d += 1
        return ans
