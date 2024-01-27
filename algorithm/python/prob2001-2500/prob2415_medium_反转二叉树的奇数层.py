from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        q0 = deque() # 偶数层节点
        q1 = deque() # 奇数层节点，当前要反转的层
        q2 = deque() # 当前反转层的下一层
        q0.append(root)
        while q0:
            # 从 q0 得到下一层 q1
            for node in q0:
                if node.left is None:
                    break
                q1.append(node.left)
                q1.append(node.right)
            if q1 is None:
                break
            # 若 q1 存在，首先获取 q1 的下一层 q2
            for node in q1:
                if node.left is None:
                    break
                q2.append(node.left)
                q2.append(node.right)
            q1.reverse()
            # 处理 q1：
            # 枚举 q0 节点并弹出，每个 q0 中的点 a：
            #     q1 中弹出 2 个节点 b1, b2，分别为 a.left，a.right
            #     若 q2 存在，q2 遍历 4 个节点 c1, c2, c3, c4，分别为 b1.left, b1.right, b2.left, b2.right
            i_q2 = 0
            while q0:
                node = q0[0]
                q0.popleft()
                node.left = q1[0]
                if q2:
                    q1[0].left = q2[i_q2]
                    i_q2 += 1
                    q1[0].right = q2[i_q2]
                    i_q2 += 1
                q1.popleft()
                node.right = q1[0]
                if q2:
                    q1[0].left = q2[i_q2]
                    i_q2 += 1
                    q1[0].right = q2[i_q2]
                    i_q2 += 1
                q1.popleft()
            q0, q2 = q2, q0
        return root
