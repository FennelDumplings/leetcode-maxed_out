class Solution:
    def removeTrailingZeros(self, num: str) -> str:
        n = len(num)
        j = n - 1
        while j >= 0 and num[j] == '0':
            j -= 1
        return num[0:j+1]
