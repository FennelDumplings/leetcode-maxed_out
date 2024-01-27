class Solution:
    def nextBeautifulNumber(self, n: int) -> int:
        self.MAX = 6
        self.L = 1
        if n > 0:
            self.L = int(math.log10(n)) + 1
        ans = [int(1e9)]
        d_list = []
        self.solve(1, n, d_list, ans)
        return ans[0]

    def solve(self, d: int, n: int, d_list: List[int], ans: List[int]) -> None:
        if len(d_list) >= self.L + 2:
            # 最优性剪枝
            return
        elif len(d_list) >= self.L:
            # 更新答案
            x = 0
            visited = [False for _ in range(len(d_list))]
            self.check(0, x, d_list, n, ans, visited)
            return

        if d > self.MAX:
            return

        # 选 d
        for _ in range(d):
            d_list.append(d)
        self.solve(d + 1, n, d_list, ans)
        for _ in range(d):
            d_list.pop()
        # 不选 d
        self.solve(d + 1, n, d_list, ans)

    def check(self, i: int, x: int, d_list: List[int], n: int, ans: List[int], visited: List[int]) -> bool:
        if i == len(d_list):
            if x > n:
                ans[0] = min(ans[0], x)
                return True
            else:
                return False
        for j, d in enumerate(d_list):
            if visited[j]:
                continue
            visited[j] = True
            x *= 10
            x += d
            if self.check(i + 1, x, d_list, n, ans, visited):
                return True
            x //= 10
            visited[j] = False
        return False
