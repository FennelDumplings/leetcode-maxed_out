import copy

class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

class Solution:
    def cloneGraph(self, node: 'Node') -> 'Node':
        if node is None:
            return None
        self.mapping = dict() # 原图某节点 -> 已拷贝后的节点
        return self.dfs(node)

    def dfs(self, node: "Node") -> "Node":
        new_node = Node(node.val)
        self.mapping[node] = new_node
        n = len(node.neighbors)
        for neighbor in node.neighbors:
            if neighbor in self.mapping:
                new_node.neighbors.append(self.mapping[neighbor])
            else:
                new_node.neighbors.append(self.dfs(neighbor))
        return new_node
