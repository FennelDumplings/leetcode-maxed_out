class Solution:
    def maximumBinaryString(self, binary: str) -> str:
        n = len(binary)
        idx0 = []
        for i in range(n):
            if binary[i] == '0':
                idx0.append(i)
        idx0.reverse()
        result = ['1'] * n
        while len(idx0) > 1:
            nxt = idx0[-1] + 1
            idx0.pop()
            idx0.pop()
            idx0.append(nxt)
        if len(idx0) > 0:
            result[idx0[0]] = '0'
        return ''.join(result)
