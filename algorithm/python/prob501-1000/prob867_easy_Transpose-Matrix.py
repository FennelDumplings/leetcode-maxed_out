class Solution:
    def transpose(self, A: List[List[int]]) -> List[List[int]]:
        return [row for row in zip(*A)]
