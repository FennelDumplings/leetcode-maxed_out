from collections import Counter

class Solution:
    def findOriginalArray(self, changed: List[int]) -> List[int]:
        n = len(changed)
        if n % 2 == 1:
            return []
        changed.sort()
        mapping = Counter()
        result = []
        for i in range(n):
            if mapping[changed[i]] > 0:
                # mapping.subtract({changed[i]: 1})
                mapping[changed[i]] -= 1
            else:
                result.append(changed[i])
                # mapping.update({2 * changed[i]: 1})
                mapping[2 * changed[i]] += 1
        s = sum(mapping.values())
        if s > 0:
            return []
        return result
