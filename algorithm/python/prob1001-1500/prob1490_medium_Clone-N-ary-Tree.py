# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children if children is not None else []

# class Solution:
#     def cloneTree(self, root: "Node") -> "Node":
#         if root is None:
#             return None
#         return self.dfs(root)
#
#     def dfs(self, node: "Node") -> "Node":
#         new_node = Node(node.val)
#         n_child = len(node.children)
#         new_node.children = [None] * n_child
#         for i, child in enumerate(node.children):
#             new_node.children[i] = self.dfs(child)
#         return new_node

import copy

# class Solution:
#     def cloneTree(self, root: 'Node') -> 'Node':
#         return copy.deepcopy(root)

import types

def __deepcopy__(self):
    def dfs(node: "Node") -> "Node":
        new_node = Node(node.val)
        n_child = len(node.children)
        new_node.children = [None] * n_child
        for i, child in enumerate(node.children):
            new_node.children[i] = dfs(child)
        return new_node
    if root is None:
        return None
    return dfs(self)

class Solution:
    def cloneTree(self, root: 'Node') -> 'Node':
        root.__deepcopy__ = types.MethodType(__deepcopy__, self)
        return copy.deepcopy(root)
