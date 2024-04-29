# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:

        def dfs(node: Optional[TreeNode]) -> int:
            # 整合子树的信息：
            # 1. 子树是否含 start
            # 2. 子树的深度，若子树含 start，则 start 子树下的节点不计深度
            h_left = h_right = 0
            s_left = s_right = False
            if node.left:
                s_left, h_left = dfs(node.left)
            if node.right:
                s_right, h_right = dfs(node.right)

            nonlocal ans
            if node.val == start:
                # 找到 start 初始化
                ans = max(h_left, h_right)
                return True, 1

            if s_left or s_right:
                ans = max(ans, h_left + h_right)

            s = s_left or s_right
            h = max(h_left, h_right) + 1
            if s_left:
                h = h_left + 1
            if s_right:
                h = h_right + 1
            return s, h

        ans = 0
        dfs(root)

        return ans
