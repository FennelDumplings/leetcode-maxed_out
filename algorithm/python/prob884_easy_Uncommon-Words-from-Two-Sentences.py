from collections import Counter

class Solution:
    def uncommonFromSentences(self, A: str, B: str) -> List[str]:
        def preprocess(s: str):
            return Counter((s.split()))
        def postprocess(cnt1, cnt2, result):
            for key in cnt1:
                if cnt1[key] > 1:
                    continue
                if cnt2.get(key, 0) > 0:
                    continue;
                result.append(key)

        cntA = preprocess(A)
        cntB = preprocess(B)
        result = []
        postprocess(cntA, cntB, result)
        postprocess(cntB, cntA, result)
        return result

