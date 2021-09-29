from collections import Counter

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def pathSum(self, root: TreeNode, targetSum: int) -> int:
        if root is None:
            return 0
        self.ans = 0
        self.presum = 0
        self.mapping = Counter()
        self.mapping.update([0])
        self._preOrder(root, targetSum)
        return self.ans

    def _preOrder(self, node: TreeNode, targetSum: int) -> None:
        self.presum += node.val
        self.ans += self.mapping[self.presum - targetSum]
        self.mapping.update([self.presum])
        if node.left is not None:
            self._preOrder(node.left, targetSum)
        if node.right is not None:
            self._preOrder(node.right, targetSum)
        self.mapping.subtract([self.presum])
        self.presum -= node.val
