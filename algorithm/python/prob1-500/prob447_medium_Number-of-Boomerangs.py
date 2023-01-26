class Solution:
    def numberOfBoomerangs(self, points: List[List[int]]) -> int:
        n = len(points)
        if n < 3:
            return 0
        ans = 0
        for i in range(n):
            # 枚举中点
            mapping = dict() # length -> cnt
            for j in range(n):
                if j == i:
                    continue
                d = self.dist(points[i], points[j])
                if d not in mapping:
                    mapping[d] = 0
                ans += 2 * mapping[d]
                mapping[d] += 1
        return ans

    def dist(self, p1, p2):
        x = p1[0] - p2[0]
        y = p1[1] - p2[1]
        return x * x + y * y

