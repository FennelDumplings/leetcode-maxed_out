def eq(p1, p2):
    return p1[0] == p2[0] and p1[1] == p2[1]

class Solution:
    def isBoomerang(self, points: List[List[int]]) -> bool:
        p1, p2, p3 = points
        if eq(p1, p2) or eq(p2, p3) or eq(p1, p3):
            return False
        if p1[0] == p2[0]:
            return p3[0] != p2[0]
        if p1[1] == p2[1]:
            return p3[1] != p2[1]
        return (p1[0] - p2[0]) * (p3[1] - p2[1]) != (p1[1] - p2[1]) * (p3[0] - p2[0])
