class Solution:
    def distanceTraveled(self, mainTank: int, additionalTank: int) -> int:
        ans = 0
        while mainTank >= 5:
            t = mainTank // 5
            r = mainTank % 5
            ans += 5 * t
            d = min(t, additionalTank)
            mainTank = r + d
            additionalTank -= d
        ans += mainTank
