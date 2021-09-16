# Definition for a binary tree node.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __hash__(self):
        MOD = 1e9+7

class Solution:
    def isSameTree(self, p: TreeNode, q: TreeNode) -> bool:
