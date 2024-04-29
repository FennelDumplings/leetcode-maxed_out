class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        q = []
        q.append(root)
        level_nodes = []
        level_sums = []
        while q:
            s = 0
            while q:
                node = q.pop()
                s += node.val
                if node.left:
                    level_nodes.append(node.left)
                if node.right:
                    level_nodes.append(node.right)
            q = level_nodes.copy()
            level_nodes.clear()
            level_sums.append(s)
        if len(level_sums) < k:
            return -1
        level_sums.sort()
        return level_sums[-k]

