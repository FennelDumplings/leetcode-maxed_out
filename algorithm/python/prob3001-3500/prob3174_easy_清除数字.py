class Solution:
    def clearDigits(self, s: str) -> str:
        result = []
        cnt = 0
        n = len(s)
        for i in range(n - 1, -1, -1):
            ch = s[i]
            if ch.islower():
                if cnt == 0:
                    result.append(ch)
                else:
                    cnt -= 1
            else:
                cnt += 1
        result.reverse()
        return "".join(result)
