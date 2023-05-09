class Solution:
    def countTime(self, time: str) -> int:
        ans = 1

        if time[0] == '?' and time[1] == '?':
            ans *= 24
        elif time[0] == '?':
            if time[1] <= '3':
                ans *= 3
            else:
                ans *= 2
        elif time[1] == '?':
            if time[0] == '2':
                ans *= 4
            else:
                ans *= 10

        if time[3] == '?' and time[4] == '?':
            ans *= 60
        elif time[3] == '?':
            ans *= 6
        elif time[4] == '?':
            ans *= 10

        return ans
