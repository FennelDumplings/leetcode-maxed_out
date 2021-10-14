class Solution:
    def reformat(self, s: str) -> str:
        n = len(s)
        n_char = 0
        for ch in s:
            if ch.isalpha():
                n_char += 1
        n_num = n - n_char
        if abs(n_num - n_char) > 1:
            return ""
        result = ["*"] * n
        if n_num > n_char:
            i_num = 0
            i_char = 1
        else:
            i_num = 1
            i_char = 0
        for i in range(n):
            if s[i].isalpha():
                result[i_char] = s[i]
                i_char += 2
            else:
                result[i_num] = s[i]
                i_num += 2
        return "".join(result)
