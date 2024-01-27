def g(i):
    n = i // 2
    return 2 * n * (n + 1) * (2 * n + 1)

def check(i, neededApples):
    # 边长为 i 的矩形，苹果数量是否大于等于 neededApples
    return g(i) >= neededApples

class Solution:
    def minimumPerimeter(self, neededApples: int) -> int:
        left = 1
        right = int(1e15)
        while left < right:
            mid = (left + right) // 2
            if check(mid, neededApples):
                right = mid
            else:
                left = mid + 1
        return left * 4
