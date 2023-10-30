class Solution:
    def punishmentNumber(self, n: int) -> int:
        ans = 0
        for i in range(1, n + 1):
            num = i ** 2
            s = str(num)
            if self.check(s, i):
                ans += num
        return ans

    bool check(self, s: str, t: int) -> bool:
        sum_ = 0
        return self.dfs(s, 0, sum_, t)

    bool dfs(self, s:str, l: int, sum_: int, t: int):
        n = len(s)
        if l == n:
            return sum_ == t
        for r in range(l, n):
            cur = int(s[l : r+1])
            sum_ += cur
            if self.dfs(s, r + 1, sum_, t):
                return True
            sum_ -= cur
        return False

