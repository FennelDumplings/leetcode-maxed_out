import re

def is_decimal_number(s: str) -> bool:
    # 正则表达式匹配十进制数，包括小数点和负号
    pattern = r'^-?\d+(\.\d+)?$'
    if re.match(pattern, s):
        return True
    else:
        return False

class Solution:
    def discountPrices(self, sentence: str, discount: int) -> str:
        words = sentence.split()
        for i, w in enumerate(words):
            if w[0] == "$" and is_decimal_number(w[1:]):
                num = float(w[1:])
                if num > 0:
                    new_number = num * (1 - discount / 100)
                    words[i] = "${:.2f}".format(new_number)
        return " ".join(words)
