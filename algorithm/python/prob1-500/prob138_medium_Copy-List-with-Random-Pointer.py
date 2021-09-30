class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random

class Solution:
    def copyRandomList(self, head: 'Node') -> 'Node':
        if head is None:
            return None
        self.mapping = dict() # 原节点 -> 对应的已经拷贝出的节点
        return self.dfs(head)

    def dfs(self, node):
        new_node = Node(node.val)
        self.mapping[node] = new_node
        if node.next is not None:
            if node.next in self.mapping:
                new_node.next = self.mapping[node.next]
            else:
                new_node.next = self.dfs(node.next)
        if node.random is not None:
            if node.random in self.mapping:
                new_node.random = self.mapping[node.random]
            else:
                new_node.random = self.dfs(node.random)
        return new_node
