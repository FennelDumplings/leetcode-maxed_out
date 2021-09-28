
# Definition for a binary tree node.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def pathSum(self, root: TreeNode, targetSum: int) -> int:
        self.ans = 0
        self.presum = 0
        self._preOrder(root, targetSum)
        return self.ans

    def _preOrder(self, node: TreeNode, targetSum: int) -> None:
        self.presum += node.val
        if self.presum == targetSum:
            self.ans += 1
        if node.left is not None:
            self._preOrder(node.left, targetSum)
        if node.right is not None:
            self._preOrder(node.right, targetSum)
        self.presum -= node.val
