def convertToBase2(n: int) -> str:
    if n == 0:
        return "0"
    result = []
    b = 2
    while n > 0:
        a = n % b
        n = n // b
        result.append(str(a))
    result.reverse()
    return "".join(result)

class Solution:
    def convertDateToBinary(self, date: str) -> str:
        dates = date.split("-")
        result = []
        for date in dates:
            n = int(date)
            result.append(convertToBase2(n))
        return "-".join(result)



