class Solution:
    def bitwiseComplement(self, n: int) -> int:
        if n == 0:
            return 1
        s = list(bin(n)[2:])
        s.reverse()
        for i in range(len(s)):
            if s[i] == "1":
                s[i] = "0"
            else:
                s[i] = "1"
        b = "".join(s)
        ans = 0
        base = 1
        for i in range(len(b)):
            ans += base * (ord(b[i]) - ord("0"))
            base *= 2
        return ans
