class Solution:
    def relocateMarbles(self, nums: List[int], moveFrom: List[int], moveTo: List[int]) -> List[int]:
        counter = Counter(nums)
        m = len(moveFrom)
        for i in range(m):
            f = moveFrom[i]
            t = moveTo[i]
            if f not in counter:
                continue
            c = counter[f]
            counter.pop(f)
            counter.update({t: c})
        result = []
        for k in counter:
            result.append(k)
        result.sort()
        return result
