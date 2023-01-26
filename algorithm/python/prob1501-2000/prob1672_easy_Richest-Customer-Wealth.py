class Solution:
    def maximumWealth(self, accounts: List[List[int]]) -> int:
        return max([sum(row) for row in accounts])
