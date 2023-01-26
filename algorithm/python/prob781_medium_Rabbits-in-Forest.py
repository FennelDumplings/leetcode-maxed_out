from collections import Counter

class Solution:
    def numRabbits(self, answers: List[int]) -> int:
        cnts = Counter(answers)
        ans = 0
        for i, cnt in cnts.items():
            if cnt <= i + 1:
                ans += i + 1
            else:
                ans += cnts[i] // (i + 1) * (i + 1)
                if cnts[i] % (i + 1) != 0:
                    ans += (i + 1)
        return ans
