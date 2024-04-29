class FrequencyTracker:

    def __init__(self):
        self.counter = Counter()
        self.mapping = Counter()


    def add(self, number: int) -> None:
        cnt = self.counter[number]
        if cnt > 0:
            self.mapping[cnt] -= 1

        self.counter.update([number])
        self.mapping.update([self.counter[number]])


    def deleteOne(self, number: int) -> None:
        cnt = self.counter[number]
        if cnt == 0:
            return
        self.mapping[cnt] -= 1
        self.counter[number] -= 1
        self.mapping.update([self.counter[number]])


    def hasFrequency(self, frequency: int) -> bool:
        return self.mapping[frequency] > 0
