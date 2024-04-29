class Solution:
    def getCoprimes(self, nums: List[int], edges: List[List[int]]) -> List[int]:
        n = len(nums)
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        # pre[p][u] := 从根到 fa 的这段前缀上，距离 u 最近且不含因子 p 的节点
        pre = [[-1 for _ in range(n)] for _ in range(51)]
        result = [-1] * n

        def dfs(u: int, fa: int):
            if fa != -1:
                # 计算 result[u]
                if math.gcd(nums[u], nums[fa]) == 1:
                    result[u] = fa
                else:
                    result[u] = pre[nums[u]][fa]
                # 推导 pre[p][u]
                for p in range(1, 51):
                    if math.gcd(p, nums[fa]) == 1:
                        pre[p][u] = fa
                    else:
                        pre[p][u] = pre[p][fa]

            for v in g[u]:
                if v == fa:
                    continue
                dfs(v, u)

        dfs(0, -1)
        return result
