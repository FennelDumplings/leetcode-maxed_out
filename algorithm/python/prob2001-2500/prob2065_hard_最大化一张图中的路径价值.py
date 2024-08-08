class Solution:
    def maximalPathQuality(self, values: List[int], edges: List[List[int]], maxTime: int) -> int:
        n = len(values)
        g = [[] for _ in range(n)]
        for u, v, w in edges:
            g[u].append((v, w))
            g[v].append((u, w))

        INF = int(1e9)

        def dijkstra(s: int) -> List[int]:
            d = [INF] * n
            d[s] = 0
            heap_data = []
            heapq.heappush(heap_data, (0, s))

            while heap_data:
                min_d, u = heapq.heappop(heap_data)
                if d[u] < min_d:
                    continue
                for v, w in g[u]:
                    if d[v] <= d[u] + w:
                        continue
                    d[v] = d[u] + w
                    heapq.heappush(heap_data, (d[v], v))

            return d

        def dfs(u: int, t: int, path_val: int) -> None:
            if t < d[u]:
                return

            nonlocal ans

            if mapping[u] == 0:
                path_val += values[u]
            mapping[u] += 1

            if u == 0:
                ans = max(ans, path_val)

            for (v, w) in g[u]:
                if w > t:
                    continue
                dfs(v, t - w, path_val)

            mapping[u] -= 1
            if mapping[u] == 0:
                path_val -= values[u]

        mapping = [0 for _ in range(n)]
        ans = 0
        path_val = 0
        d = dijkstra(0)
        dfs(0, maxTime, path_val)

        return ans
