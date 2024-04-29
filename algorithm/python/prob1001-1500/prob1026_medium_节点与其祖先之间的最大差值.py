INF = int(1e10)

class Solution:
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        ans = 0

        def dfs(node: int) -> List[int]:
            left = right = [INF, -INF]
            if node.left:
                left = dfs(node.left)
            if node.right:
                right = dfs(node.right)

            m = node.val
            m = min(m, left[0])
            m = min(m, right[0])
            M = node.val
            M = max(M, left[1])
            M = max(M, right[1])

            nonlocal ans
            ans = max(ans, abs(node.val - m))
            ans = max(ans, abs(M - node.val))

            return [m, M]

        dfs(root)
        return ans

