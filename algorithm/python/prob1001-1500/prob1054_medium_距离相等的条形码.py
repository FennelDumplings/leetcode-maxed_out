from functools import cmp_to_key
from collections import Counter
from queue import PriorityQueue

class Item:
    def __init__(self, v: int=-1, cnt: int=0):
        self.v = v
        self.cnt = cnt

    def __repr__(self):
        return "v: {}, cnt: {}".format(self.v, self.cnt)


class HeapCmp:
    def __call__(self, i1: Item, i2: Item) -> bool:
        # 在堆中按 cnt 从大到小
        if i1.cnt < i2.cnt:
            return 1
        elif i1.cnt > i2.cnt:
            return -1
        else:
            return 0

class Solution:
    def rearrangeBarcodes(self, barcodes: List[int]) -> List[int]:
        n = len(barcodes)
        if n <= 2:
            return barcodes
        MAX_VAL = 10000
        cnts = Counter(barcodes)

        mycmp = HeapCmp()
        mykey = cmp_to_key(mycmp)
        pq = PriorityQueue()
        for i in range(1, MAX_VAL + 1):
            if cnts[i] == 0:
                continue
            item = Item(i, cnts[i])
            pq.put(mykey(item))

        result = [-1] * n
        odd = True
        _iter = 0
        while not pq.empty():
            item = pq.get()
            print(item.obj)
            cnt = item.obj.cnt
            while _iter < n and cnt > 0:
                result[_iter] = item.obj.v
                _iter += 2
                cnt -= 1
            if _iter >= n and odd:
                odd = False
                _iter = 1
                while _iter < n and cnt > 0:
                    result[_iter] = item.obj.v
                    _iter += 2
                    cnt -= 1
        return result
