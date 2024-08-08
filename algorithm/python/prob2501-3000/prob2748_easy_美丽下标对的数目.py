def check(x, y):
    a = 0
    while x > 0:
        a = x % 10
        x //= 10
    b = y % 10
    if math.gcd(a, b) == 1:
        return True
    return False

class Solution:
    def countBeautifulPairs(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0
        for i in range(n - 1):
            for j in range(i + 1, n):
                if check(nums[i], nums[j]):
                    ans += 1
        return ans
