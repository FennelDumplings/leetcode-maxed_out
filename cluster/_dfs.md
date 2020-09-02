DFS 可解决的问题

组合搜索和隐式图搜索 `_combinatorics.md`

常见办法

  - 复杂状态表示和状态转移
    - [282. 给表达式添加运算符](https://leetcode-cn.com/problems/expression-add-operators/)
    - [291. 单词规律 II](https://leetcode-cn.com/problems/word-pattern-ii/)
    - [388. 文件的最长绝对路径](https://leetcode-cn.com/problems/longest-absolute-file-path/)
    - [529. 扫雷游戏](https://leetcode-cn.com/problems/minesweeper/)
    - [1391. 检查网格中是否存在有效路径](https://leetcode-cn.com/problems/check-if-there-is-a-valid-path-in-a-grid/) 
  - 状态压缩
    - [638. 大礼包](https://leetcode-cn.com/problems/shopping-offers/)
    - [464. 我能赢吗](https://leetcode-cn.com/problems/can-i-win/) 状态压缩+记忆化dfs
  - 记忆化
    - [面试题 16.11. 跳水板](https://leetcode-cn.com/problems/diving-board-lcci/)
    - [面试题 17.13. 恢复空格](https://leetcode-cn.com/problems/re-space-lcci/)
  - 剪枝
    - [488. 祖玛游戏](https://leetcode-cn.com/problems/zuma-game/) 大量剪枝
    - [956. 最高的广告牌](https://leetcode-cn.com/problems/tallest-billboard/) 剪枝，搜索顺序
    - [面试题 17.25. 单词矩阵](https://leetcode-cn.com/problems/word-rectangle-lcci/)
  - 搜索顺序
    - [473. 火柴拼正方形](https://leetcode-cn.com/problems/matchsticks-to-square/)  
    - [698. 划分为k个相等的子集](https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/) 可以对状态压缩后的整数做记忆化
  - 迭代加深
    - [41. 困于环中的机器人](https://leetcode-cn.com/problems/robot-bounded-in-circle/)
  - IDAstar
    - [1091. 二进制矩阵中的最短路径](https://leetcode-cn.com/problems/shortest-path-in-binary-matrix/)
  - minimax 和 alpha-veta 剪枝(博弈树模型)
    - [486. 预测赢家](https://leetcode-cn.com/problems/predict-the-winner/)
