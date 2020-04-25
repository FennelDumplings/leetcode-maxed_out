
# 树遍历基本操作

| 前序 | 中序 | 后序 | 层序
---|--- | --- | --- | ---
递归 | 递归 | 递归  | 队列
迭代 | 迭代 | 迭代  | 递归(不用队列2)
morris 遍历 | morris 遍历 | morris 遍历 | 双指针(不用队列2) 


# 树遍历基本操作题目列表
## 二叉树

[94. 二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)  
[144. 二叉树的前序遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)  
[145. 二叉树的后序遍历](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/)  
[102. 二叉树的层序遍历](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)  

## N 叉树(类似邻接表)
[589. N叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/)  
[590. N叉树的后序遍历](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/)  
[429. N叉树的层序遍历](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/)  

# 树遍历应用题目列表
## 1. 前序遍历
### 序列化
重建树的方法：
1. 前序 + 中序
2. 中序 + 后序
3. 前序/后序 + null标记

当节点值很大时候，节点值统一转成16进制字符串(4字节)

#### 题目列表：
[297. 二叉树的序列化与反序列化](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)  
[271. 字符串的编码与解码](https://leetcode-cn.com/problems/serialize-and-deserialize-bst/)  
[428. 序列化和反序列化 N 叉树](https://leetcode-cn.com/problems/serialize-and-deserialize-n-ary-tree/)  

### 其它
#### 题目列表
[255. 验证前序遍历序列二叉搜索树](https://leetcode-cn.com/problems/verify-preorder-sequence-in-binary-search-tree/)  
[431. 将 N 叉树编码为二叉树](https://leetcode-cn.com/problems/encode-n-ary-tree-to-binary-tree/)  

## 2. 中序遍历
### 二叉搜索树
#### 题目列表
[98. 验证二叉搜索树](https://leetcode-cn.com/problems/validate-binary-search-tree/)  
[501. 二叉搜索树中的众数](https://leetcode-cn.com/problems/find-mode-in-binary-search-tree/)  
[230. 二叉搜索树中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/)  
[272. 最接近的二叉搜索树值 II](https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/)  
[530. 二叉搜索树的最小绝对差](https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/) / [783. 二叉搜索树节点最小距离](https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/)  
[99. 恢复二叉搜索树](https://leetcode-cn.com/problems/recover-binary-search-tree/)(follow up 是 morris 中序遍历)  

### 前驱后继(非递归中序遍历)
[285. 二叉搜索树中的顺序后继](https://leetcode-cn.com/problems/inorder-successor-in-bst/)  
[510. 二叉搜索树中的中序后继 II](https://leetcode-cn.com/problems/inorder-successor-in-bst-ii/)  
[173. 二叉搜索树迭代器](https://leetcode-cn.com/problems/binary-search-tree-iterator/)  

## 3. 后序遍历
### 类似树形DP的问题
[979. 在二叉树中分配硬币](https://leetcode-cn.com/problems/distribute-coins-in-binary-tree/)  
[968. 监控二叉树](https://leetcode-cn.com/problems/binary-tree-cameras/)  

## 4. 层序遍历
[107. 二叉树的层次遍历 II](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)  
[637. 二叉树的层平均值](https://leetcode-cn.com/problems/average-of-levels-in-binary-tree/)  
[103. 二叉树的锯齿形层次遍历](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)  
[993. 二叉树的堂兄弟节点](https://leetcode-cn.com/problems/cousins-in-binary-tree/)  
