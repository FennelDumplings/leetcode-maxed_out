class Solution:
    def numPairsDivisibleBy60(self, time: List[int]) -> int:
        counter = Counter()
        ans = 0
        for t in time:
            ans += counter[(120 - (t % 60)) % 60]
            counter[t % 60] += 1
        return ans
