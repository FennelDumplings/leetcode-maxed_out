class OrderedStream:
    def __init__(self, n: int):
        self.items = [""] * n
        self.ptr = 1

    def insert(self, idKey: int, value: str) -> List[str]:
        self.items[idKey - 1] = value
        result = []
        n = len(self.items)
        if self.ptr == idKey:
            i = self.ptr - 1
            while i < n and self.items[i] != "":
                result.append(self.items[i])
                i += 1
            self.ptr = i + 1
        return result


# Your OrderedStream object will be instantiated and called as such:
# obj = OrderedStream(n)
# param_1 = obj.insert(idKey,value)
