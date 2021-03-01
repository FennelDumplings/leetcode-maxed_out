class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        dict1 = {s: idx for idx, s in enumerate(list1)}
        dict2 = {s: idx for idx, s in enumerate(list2)}
        result = []
        min_idx_sum = len(list1) + len(list2)
        for s, idx1 in dict1.items():
            idx2 = dict2.get(s, -1)
            if idx2 != -1:
                idx_sum = idx1 + idx2
                if idx_sum < min_idx_sum:
                    result = [s]
                    min_idx_sum = idx_sum
                elif idx_sum == min_idx_sum:
                    result.append(s)
        return result
