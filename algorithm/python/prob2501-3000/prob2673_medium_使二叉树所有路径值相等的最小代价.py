class Solution:
    def minIncrements(self, n: int, cost: List[int]) -> int:
        self.ans = 0
        self.cost = cost
        self.n = n
        self.preOrder(1)
        return self.ans

    def preOrder(self, node: int) ->int:
        # 返回以 node 为根的子树，最长路径的和
        if node * 2 > self.n:
            return self.cost[node - 1]
        left = node * 2
        right = node * 2 + 1
        left_sum = self.preOrder(left)
        right_sum = self.preOrder(right)
        self.ans += abs(left_sum - right_sum)
        return max(left_sum, right_sum) + self.cost[node - 1]
