class Solution:
    def finalValueAfterOperations(self, operations: List[str]) -> int:
        X = 0
        for s in operations:
            if s[:2] == "--" or s[1:] == "--":
                X -= 1
            else:
                X += 1
        return X
