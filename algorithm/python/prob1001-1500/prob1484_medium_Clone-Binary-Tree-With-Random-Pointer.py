class Node:
    def __init__(self, val=0, left=None, right=None, random=None):
        self.val = val
        self.left = left
        self.right = right
        self.random = random

class NodeCopy:
    def __init__(self, val=0, left=None, right=None, random=None):
        self.val = val
        self.left = left
        self.right = right
        self.random = random

class Solution:
    def copyRandomBinaryTree(self, root: 'Node') -> 'NodeCopy':
        if root is None:
            return None
        self.mapping = dict() # 原节点 -> 对应的已拷贝的节点
        return self.dfs(root)

    def dfs(self, node: "Node") -> "NodeCopy":
        new_node = NodeCopy(node.val)
        self.mapping[node] = new_node
        if node.left is not None:
            if node.left in self.mapping:
                new_node.left = self.mapping[node.left]
            else:
                new_node.left = self.dfs(node.left)
        if node.right is not None:
            if node.right in self.mapping:
                new_node.right = self.mapping[node.right]
            else:
                new_node.right = self.dfs(node.right)
        if node.random is not None:
            if node.random in self.mapping:
                new_node.random = self.mapping[node.random]
            else:
                new_node.random = self.dfs(node.random)
        return new_node
