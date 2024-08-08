def get_primes(n: int) -> List[int]:
    if n < 2:
        return{}
    vec = [True] * n
    vec[0] = False
    vec[1] = False
    cnt = 0
    primes = []
    for i in range(2, n):
        if vec[i]:
            cnt += 1
            primes.append(i)
        for j in range(cnt):
            if i * primes[j] >= n:
                break
            vec[i * primes[j]] = False
            if i % primes[j] == 0:
                break
    return primes

class Solution:
    def maximumPrimeDifference(self, nums: List[int]) -> int:
        primes = set(get_primes(101))
        n = len(nums)
        mini = n
        maxi = -1
        for i in range(n):
            if nums[i] in primes:
                mini = min(mini, i)
                maxi = max(maxi, i)
        return maxi - mini

