from collections import Counter

class Item:
    def __init__(self, l):
        self.v0 = l[0]
        self.v1 = l[1]

    def __eq__(self, item):
        return self.v0 == item.v0 and self.v1 == item.v1 \
                or self.v0 == item.v1 and self.v1 == item.v0

    def __hash__(self):
        if self.v0 > self.v1:
            return self.v1 * 10 + self.v0
        return self.v0 * 10 + self.v1

class Solution:
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:
        counter = Counter()
        for x in dominoes:
            counter[Item(x)] += 1
        ans = 0
        for k in counter:
            cnt = counter[k]
            ans += cnt * (cnt - 1) // 2
        return ans

class Solution1:
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:
        counter = Counter()
        for x in dominoes:
            v0, v1 = x
            if v0 > v1:
                counter[v1 * 9 + v0] += 1
            else:
                counter[v0 * 9 + v1] += 1
        ans = 0
        for k in counter:
            cnt = counter[k]
            ans += cnt * (cnt - 1) // 2
        return ans
