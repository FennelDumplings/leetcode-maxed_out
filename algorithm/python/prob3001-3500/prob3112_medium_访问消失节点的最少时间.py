INF = int(1e10)

class Solution:
    def minimumTime(self, n: int, edges: List[List[int]], disappear: List[int]) -> List[int]:
        def dijkstra_heap(g: List[List[int]], start: int, N: int) -> List[int]:
            # N 个节点，节点编号从 0 开始
            d = [INF] * N
            d[start] = 0

            # 堆中维护 (到start最短距离，节点编号)
            heap_data = []
            heapq.heappush(heap_data, (0, start))

            while heap_data:
                min_d, u = heapq.heappop(heap_data)
                if d[u] < min_d:
                    continue
                for son in g[u]:
                    v, w = son
                    if d[v] <= d[u] + w:
                        continue
                    if disappear[v] <= d[u] + w:
                        continue
                    d[v] = d[u] + w
                    heapq.heappush(heap_data, (d[v], v))

            for i in range(N):
                if d[i] == INF:
                    d[i] = -1

            return d

        g = [[] for _ in range(n)]
        for u, v, l in edges:
            g[u].append((v, l))
            g[v].append((u, l))

        return dijkstra_heap(g, 0, n)
