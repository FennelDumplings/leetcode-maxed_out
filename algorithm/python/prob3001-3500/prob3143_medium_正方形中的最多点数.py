INF = int(2e9)

class Solution:
    def maxPointsInsideSquare(self, points: List[List[int]], s: str) -> int:
        n = len(points)
        # mapping[t] 表示种类 t 的最小、次小半径
        mapping = {}
        for i in range(n):
            x, y = points[i]
            r = max(abs(x), abs(y))
            if s[i] not in mapping:
                mapping[s[i]] = [r, INF]
            else:
                if r < mapping[s[i]][0]:
                    mapping[s[i]][1] = mapping[s[i]][0]
                    mapping[s[i]][0] = r
                elif r < mapping[s[i]][1]:
                    mapping[s[i]][1] = r
        max_r = INF
        minx_list = []
        for key in mapping:
            minx, sub_minx = mapping[key]
            minx_list.append(minx)
            if sub_minx == INF:
                continue
            else:
                max_r = min(max_r, sub_minx - 1)
        ans = len(list(filter(lambda minx: minx <= max_r, minx_list)))


        return ans
