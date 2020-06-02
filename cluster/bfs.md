
## 一些常见的办法
#### 双端队列
#### 优先级队列(dijkstra)
#### 多源BFS
#### 双向BFS
#### 状态压缩
#### 常数优化

---

## 字符串
当相邻节点间关系有明确约束时，可以不建图
[126. 单词接龙 II](https://leetcode-cn.com/problems/word-ladder-ii/) 不建图，双向BFS+DFS
[127. 单词接龙](https://leetcode-cn.com/problems/word-ladder/) 不建图，双向BFS
[752. 打开转盘锁](https://leetcode-cn.com/problems/open-the-lock/) 不建图，双向BFS(边稠密，收益极大)

## 迷宫系列

## 矩阵系列
[542. 01 矩阵](https://leetcode-cn.com/problems/01-matrix/) 多源 BFS
[1162. 地图分析](https://leetcode-cn.com/problems/as-far-from-land-as-possible/) 多源 BFS
[1368. 使网格图至少有一条有效路径的最小代价](https://leetcode-cn.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/) 双端队列
[675. 为高尔夫比赛砍树](https://leetcode-cn.com/problems/cut-off-trees-for-golf-event/) BFS 常数优化 tricks，Hadlock
[778. 水位上升的泳池中游泳](https://leetcode-cn.com/problems/swim-in-rising-water/) 优先级队列
[864. 获取所有钥匙的最短路径](https://leetcode-cn.com/problems/shortest-path-to-get-all-keys/) 状态压缩
[934. 最短的桥](https://leetcode-cn.com/problems/shortest-bridge/) DFS+BFS

