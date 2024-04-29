class Solution:
    def finalString(self, s: str) -> str:
        s = self.preprocess(s)
        items = s.split("i")
        ni = len(items) - 1 # i 的个数
        # items[j] 右边有 ni - j 个 i，若 (ni - i) % 2 为 1 则需要反转
        ans = []
        for j in range(ni - 1, -1, -2):
            ans.append(items[j][::-1])
        for j in reversed(range(ni - 2, -1, -2)):
            ans.append(items[j])
        ans.append(items[ni])
        return "".join(ans)

    def preprocess(self, s: str) -> str:
        result = []
        n = len(s)
        i = 0
        while i < n and s[i] == "i":
            i += 1
        while i < n:
            j = i
            while j < n and s[j] != "i":
                j += 1
            result.append(s[i:j])
            if j == n:
                break
            i = j
            while j < n and s[j] == "i":
                j += 1
            if (j - i) % 2 == 1:
                result.append("i")
            i = j
        print(result)
        return "".join(result)
