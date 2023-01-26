# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findTilt(self, root: TreeNode) -> int:
        if root is None:
            return 0
        self.ans = 0
        self.dfs(root)
        return self.ans

    def dfs(self, node: TreeNode) -> int:
        left_sum = right_sum = 0
        if node.left is not None:
            left_sum = self.dfs(node.left)
        if node.right is not None:
            right_sum = self.dfs(node.right)
        self.ans += abs(left_sum - right_sum)
        return left_sum + right_sum + node.val
