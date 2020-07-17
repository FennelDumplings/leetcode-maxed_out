
# 树遍历基本方式
## 树遍历的背景介绍
树的遍历是指按照某种顺序将树中所有节点的数据访问一遍。这个过程类似与搜索，比如要在树中判断某个值是否存在，需要把树的所有节点值访问一遍。  

树的常用遍历方式有前序，中序，后序，层序。

按照搜索的视角来理解，前序，中序，后序类似 DFS 搜索过程。层序类似 BFS 搜索过程。

树的遍历最常见的应用:   
1. 很多上下游的程序之间需要传递某些参数，变量。这些参数或者变量经常是用 xml 或 json 形式存储的，xml 和 json。例如上游将一些信息写成 json 之后通过某些渠道(例如 Redis 等)，打给下游。下游接到 json 之后需要把信息解析出来，这个过程是树的遍历。
2. 很多代码的部署需要一些配置文件，例如 yaml，里面的字段和值也是树形结构组织的。代码要跑起来需要先解析这些参数和值，这个过程就是树的遍历。

前序: 递归、迭代、Morris遍历  
中序: 递归、迭代、Morris遍历  
后序: 递归、迭代、Morris遍历  
层序: 队列、递归(不用队列1)、双指针(不用队列2)  

Morris 遍历在遍历中充分利用了 null 指针的空间，空间性能较好，但是比较复杂，也不像递归和迭代那样是通用的算法思想，有很多延伸的问题，可以选择性掌握，力扣上的题目也很少，可以参考[99. 恢复二叉搜索树](https://leetcode-cn.com/problems/recover-binary-search-tree/) 的 follow up。 

# 树遍历基本操作题目列表
## 二叉树

### 什么是二叉树
在树结构的基础上，每个节点最多有两个子节点的树为 2 叉树  

[94. 二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)  
[144. 二叉树的前序遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)  
[145. 二叉树的后序遍历](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/)  
[102. 二叉树的层序遍历](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)  

## N 叉树(类似邻接表)
### 什么是 N 叉树
N 叉树是指每个节点最多可以有 N 个子节点的树形结构。实现起来比 2 叉树难度大一些，但是可以解决二叉树高度比较高的不足。

1. B 树是 N 叉树  
2. Trie 树是 N 叉树  
3. 归并排序过程也对应这一个树形结构，称为归并树，可以解决查询区间上大于 x 的元素个数问题。如果归并路数 N > 2，对应的是一个 N 路归并树，它是一个 N 叉树，主要用于外排序中归并的步骤，减少磁盘读写次数。

[589. N叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/)  
[590. N叉树的后序遍历](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/)  
[429. N叉树的层序遍历](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/)  

# 树遍历应用题目列表
## 1. 前序遍历
### 序列化
#### 什么是序列化
序列化是指将内存中的数据结构转化成字符串，然后写入到文件，以便于存储和传输。

例如上面提到的上下游的程序之间可以用 json 传递信息。上游的信息经常是内存中的数据结构(也就是对象)，把它先转换成字符串也就是序列化，然后在传输，下游接到 json 后先反序列化，也就是把字符串在变回内存中的对象，在进行后续的业务逻辑。

重建树的方法：
1. 前序 + 中序
2. 中序 + 后序
3. 前序/后序 + null标记

当节点值很大时候，节点值统一转成16进制字符串(4字节)

#### 题目列表：
[297. 二叉树的序列化与反序列化](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)  
[449. 字符串的编码与解码](https://leetcode-cn.com/problems/serialize-and-deserialize-bst/)  
[428. 序列化和反序列化 N 叉树](https://leetcode-cn.com/problems/serialize-and-deserialize-n-ary-tree/)  
[1028. 从先序遍历还原二叉树](https://leetcode-cn.com/problems/recover-a-tree-from-preorder-traversal/) 迭代法
[606]
[536]
[652]

### 其它
#### 题目列表
[255. 验证前序遍历序列二叉搜索树](https://leetcode-cn.com/problems/verify-preorder-sequence-in-binary-search-tree/)  
[431. 将 N 叉树编码为二叉树](https://leetcode-cn.com/problems/encode-n-ary-tree-to-binary-tree/)  
[513]
[536]
 
##### 结构判断
[100]
[578]
[1367]

## 2. 中序遍历
### 二叉搜索树
#### 题目列表
[98. 验证二叉搜索树](https://leetcode-cn.com/problems/validate-binary-search-tree/)  
[501. 二叉搜索树中的众数](https://leetcode-cn.com/problems/find-mode-in-binary-search-tree/)  
[230. 二叉搜索树中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/)  
[272. 最接近的二叉搜索树值 II](https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/)  
[530. 二叉搜索树的最小绝对差](https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/)
[99. 恢复二叉搜索树](https://leetcode-cn.com/problems/recover-binary-search-tree/)(follow up 是 morris 中序遍历)  
[426. 将二叉搜索树转化为排序的双向链表](https://leetcode-cn.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/)
[530. 二叉搜索树的最小绝对差](https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/)
[783. 二叉搜索树节点最小距离](https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/submissions/) (用引用维护 prev)

### 前驱后继(非递归中序遍历)
[285. 二叉搜索树中的顺序后继](https://leetcode-cn.com/problems/inorder-successor-in-bst/)  
[510. 二叉搜索树中的中序后继 II](https://leetcode-cn.com/problems/inorder-successor-in-bst-ii/)  
[173. 二叉搜索树迭代器](https://leetcode-cn.com/problems/binary-search-tree-iterator/)  


## 3. 后序遍历
### 类似树形DP的问题
[979. 在二叉树中分配硬币](https://leetcode-cn.com/problems/distribute-coins-in-binary-tree/)  
[968. 监控二叉树](https://leetcode-cn.com/problems/binary-tree-cameras/)  
[508. 出现次数最多的子树元素和](https://leetcode-cn.com/problems/most-frequent-subtree-sum/)  
[250. 统计同值子树](https://leetcode-cn.com/problems/count-univalue-subtrees/)  
[549]
[563]
[124]
[742]
// BST 子树
[323]
[1371]
- [1273. 删除树节点](https://leetcode-cn.com/problems/delete-tree-nodes/)  

## 4. 层序遍历
[107. 二叉树的层次遍历 II](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)  
[637. 二叉树的层平均值](https://leetcode-cn.com/problems/average-of-levels-in-binary-tree/)  
[103. 二叉树的锯齿形层次遍历](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)  
[993. 二叉树的堂兄弟节点](https://leetcode-cn.com/problems/cousins-in-binary-tree/)  

## 5. 树的重建
[105. 从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)  
[106. 从中序与后序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)  
[1028. 从前序遍历还原二叉树]
[889. 根据前序和后序遍历构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)
[1008. 先序遍历构造二叉树]

## 6. 垂序遍历
[314. 二叉树的垂直遍历](https://leetcode-cn.com/problems/binary-tree-vertical-order-traversal/)  
[987. 二叉树的垂序遍历](https://leetcode-cn.com/problems/vertical-order-traversal-of-a-binary-tree/)  

## 7. 树上 dfs
[199. 二叉树的右视图](https://leetcode-cn.com/problems/binary-tree-right-side-view/)  
[545. 二叉树的边界](https://leetcode-cn.com/problems/boundary-of-binary-tree/)  

## 8. 树上 bfs 和 dfs 均可的题
[513]
[515]
[623]

## 9. 最近公共祖先
[1257. 最小公共区域](https://leetcode-cn.com/problems/smallest-common-region/)
[235. 二叉搜索树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)
[236. 二叉树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)
[1123. 最深叶节点的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-deepest-leaves/)
[面试题 04.08. 首个共同祖先](https://leetcode-cn.com/problems/first-common-ancestor-lcci/)
[1483. 树节点的第 K 个祖先](https://leetcode-cn.com/problems/kth-ancestor-of-a-tree-node/) 倍增法求LCA, DFS序

## 10. 四叉树

## 11. 两次遍历
[655]
[310]
[863] 第一次dfs添加父节点指针， 建立建邻接表后bfs, 第二次从目标节点开始 bfs
[834] 邻接表形式，后序接前序
[865] 后序接前序

## 12. 数组形式的二叉树
[666] 树确定很小

## 13. 邻接表形式的树
[1245]
[834] 与子节点和父节点均有关系，后序接前序
[1443. 收集树上所有苹果的最少时间](https://leetcode-cn.com/problems/minimum-time-to-collect-all-apples-in-a-tree/)
