class Solution:
    def checkIfExist(self, arr: List[int]) -> bool:
        target_set = set()
        for x in arr:
            if x in target_set:
                return True
            target_set.add(x * 2)
            if x % 2 == 0:
                target_set.add(x // 2)
        return False
