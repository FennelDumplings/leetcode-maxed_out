

import numpy as np

class Solution:
    def game(self, guess: List[int], answer: List[int]) -> int:
        arr1 = np.array(guess)
        arr2 = np.array(answer)
        return int(np.sum(arr1 == arr2))
