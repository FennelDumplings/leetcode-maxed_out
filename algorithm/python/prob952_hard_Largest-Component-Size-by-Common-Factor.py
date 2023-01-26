class Solution:
    def largestComponentSize(self, A: List[int]) -> int:
        max_num = max(A)
        p = list(range(max_num + 1))

        def get_root(x: int):
            if p[x] != x:
                p[x] = get_root(p[x])
            return p[x]

        in_A = [False] * (max_num + 1)
        for a in A:
            in_A[a] = True  # 判断是否在A里

        is_primes = [True] * (max_num + 1)  # 预设为质数
        for i in range(2, max_num + 1):
            if is_primes[i]:
                for j in range(i + i, max_num + 1, i):  # 质数的倍数都不是质数
                    if in_A[j]:
                        p[get_root(j)] = get_root(i)  ## 并到质数上
                    is_primes[j] = False

        count = collections.Counter()
        for a in A:
            count[get_root(a)] += 1

        return max(count.values())
