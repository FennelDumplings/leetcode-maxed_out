class Solution:
    def minimumOperations(self, num: str) -> int:
        n = len(num)
        ans = 0
        flag0 = False
        flag5 = False
        i = n - 1
        while i >= 0:
            if flag0 and (num[i] == "0" or num[i] == "5"):
                return ans if not flag5 else ans + 1
            if flag5 and (num[i] == "2" or num[i] == "7"):
                return ans if not flag0 else ans + 1
            if not flag0 and num[i] == "0":
                flag0 = True
            elif not flag5 and num[i] == "5":
                flag5 = True
            else:
                ans += 1
            i -= 1
        return ans if not flag5 else ans + 1
