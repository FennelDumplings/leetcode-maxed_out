
def ignore_args(*args_to_ignore):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            new_args = [arg for arg in args if arg not in args_to_ignore]
            return func(*new_args, **kwargs)
        return wrapper
    return decorator

class Solution:
    def minimumTotalPrice(self, n: int, edges: List[List[int]], price: List[int], trips: List[List[int]]) -> int:
        self.g = [[] for _ in range(n)]
        for u, v in edges:
            self.g[u].append(v)
            self.g[v].append(u)

        ans = 0
        cnt = [0 for _ in range(n)]
        for s, t in trips:
            path = []
            self.get_path(s, -1, t, path)
            for u in path:
                cnt[u] += 1
                ans += price[u]

        self.f = [0 for _ in range(n)]
        for i in range(n):
            self.f[i] = cnt[i] * price[i]

        T1 = self.solve(0, 0, -1)
        T2 = self.solve(0, 1, -1)
        T = max(T1, T2)
        ans -= T / 2

        return ans


    @ignore_args("fa")
    @lru_cache(int(1e7))
    def solve(self, u, s, fa):
        if len(self.g[u]) == 1:
            return self.f[u] if s == 1 else 0

        ans = 0
        for v in self.g[u]:
            if v == fa:
                continue
            if s == 0:
                ans += max(self.solve(v, 0), self.solve(v, 1))
            else:
                ans += self.solve(v, 0)
        if s == 1:
            ans += self.f[u]

        return ans

    def get_path(self, u, fa, t, path):
        path.append(u)
        if u == t:
            return True
        for v in self.g[u]:
            if v == fa:
                continue
            if self.get_path(v, u, t, path):
                return True
        path.pop()
        return False
