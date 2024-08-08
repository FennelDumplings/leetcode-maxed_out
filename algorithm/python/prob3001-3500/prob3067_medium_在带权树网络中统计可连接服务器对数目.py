class Solution:
    def countPairsOfConnectableServers(self, edges: List[List[int]], signalSpeed: int) -> List[int]:
        n = len(edges) + 1
        g = [[] for _ in range(n)]
        for u, v, w in edges:
            g[u].append((v, w))
            g[v].append((u, w))

        def dfs(u, prev, pre_sum):
            cnt = 0
            if pre_sum % signalSpeed == 0:
                cnt += 1
            for (v, w) in g[u]:
                if v == prev:
                    continue
                cnt += dfs(v, u, pre_sum + w)
            return cnt

        result = [0] * n
        for s in range(n):
            cnts = []
            for (u, w) in g[s]:
                c = dfs(u, s, w)
                if c == 0:
                    continue
                cnts.append(c)
            if (len(cnts) < 2):
                continue
            left_sum = cnts[0]
            r = 0
            for i in range(1, len(cnts)):
                r += cnts[i] * left_sum
                left_sum += cnts[i]
            result[s] = r

        return result
