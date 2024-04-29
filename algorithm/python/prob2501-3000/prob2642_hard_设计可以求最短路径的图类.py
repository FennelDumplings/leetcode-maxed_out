class Graph:

    def __init__(self, n: int, edges: List[List[int]]):
        self.INF = int(1e11)
        self.n = n
        self.dp = [[self.INF for _ in range(n)] for _ in range(n)]
        for i in range(n):
            self.dp[i][i] = 0
        for u, v, w in edges:
            self.dp[u][v] = w

        for k in range(n):
            for i in range(n):
                for j in range(n):
                    self.dp[i][j] = min(self.dp[i][j], self.dp[i][k] + self.dp[k][j])

    def addEdge(self, edge: List[int]) -> None:
        u, v, w = edge
        for i in range(self.n):
            for j in range(self.n):
                self.dp[i][j] = min(self.dp[i][j], self.dp[i][u] + w + self.dp[v][j])


    def shortestPath(self, node1: int, node2: int) -> int:
        ans = self.dp[node1][node2]
        return ans if ans != self.INF else -1



# Your Graph object will be instantiated and called as such:
# obj = Graph(n, edges)
# obj.addEdge(edge)
# param_2 = obj.shortestPath(node1,node2)
