BFS 可解决的问题


## 一些常见的办法
#### 双端队列
[272. 最接近的二叉搜索树值 II](https://leetcode-cn.com/problems/closest-binary-search-tree-value-ii/)
[1368. 使网格图至少有一条有效路径的最小代价](https://leetcode-cn.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/)
[1263. 推箱子](https://leetcode-cn.com/problems/minimum-moves-to-move-a-box-to-their-target-location/) 状态比较复杂，取决于两个点

#### 优先级队列(dijkstra)
[778. 水位上升的泳池中游泳](https://leetcode-cn.com/problems/swim-in-rising-water/)

### 随机队列


#### 多源BFS
[286. 墙与门](https://leetcode-cn.com/problems/walls-and-gates/) 多源 BFS
[542. 01 矩阵](https://leetcode-cn.com/problems/01-matrix/)
[1162. 地图分析](https://leetcode-cn.com/problems/as-far-from-land-as-possible/)

#### 双向BFS
[127. 单词接龙](https://leetcode-cn.com/problems/word-ladder/) 不建图，双向BFS
[面试题 17.22. 单词转换](https://leetcode-cn.com/problems/word-transformer-lcci/) 没说要最短，直接 DFS 即可无需 BFS
[752. 打开转盘锁](https://leetcode-cn.com/problems/open-the-lock/) 不建图，双向BFS(边稠密，收益极大)

#### 状态压缩
[864. 获取所有钥匙的最短路径](https://leetcode-cn.com/problems/shortest-path-to-get-all-keys/)

#### 常数优化
[675. 为高尔夫比赛砍树](https://leetcode-cn.com/problems/cut-off-trees-for-golf-event/)

#### BFS+DFS
[126. 单词接龙 II](https://leetcode-cn.com/problems/word-ladder-ii/) 不建图，双向BFS+DFS
[934. 最短的桥](https://leetcode-cn.com/problems/shortest-bridge/) DFS+BFS

#### 染色
[913. 猫和老鼠](https://leetcode-cn.com/problems/cat-and-mouse/)

#### Astar

---

## Flood Fill
[994. 腐烂的橘子](https://leetcode-cn.com/problems/rotting-oranges/)
[317. 离建筑物最近的距离](https://leetcode-cn.com/problems/shortest-distance-from-all-buildings/)
[面试题 08.10. 颜色填充](https://leetcode-cn.com/problems/color-fill-lcci/)


#### 迷宫系列
[490. 迷宫](https://leetcode-cn.com/problems/the-maze/)
[505. 迷宫 II](https://leetcode-cn.com/problems/the-maze-ii/)
[499. 迷宫 III](https://leetcode-cn.com/problems/the-maze-iii/)
[1036. 逃离大迷宫](https://leetcode-cn.com/problems/escape-a-large-maze/)
[1391. 检查网格中是否存在有效路径](https://leetcode-cn.com/problems/check-if-there-is-a-valid-path-in-a-grid/) 迷宫图上的连通图问题，也可以DFS，从比较难的插头DP来的
[1210. 穿过迷宫的最少移动次数](https://leetcode-cn.com/problems/minimum-moves-to-reach-target-with-rotations/)
[LCP 13. 寻宝](https://leetcode-cn.com/problems/xun-bao/)

