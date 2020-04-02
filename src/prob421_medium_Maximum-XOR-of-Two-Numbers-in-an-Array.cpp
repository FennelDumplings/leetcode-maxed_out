// prob 421: Maximum XOR of Two Numbers in an Array

/*
 * Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.
 * Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.
 * Could you do this in O(n) runtime?
 */

/*
 * Example:
 * Input: [3, 10, 5, 25, 2, 8]
 * Output: 28
 * Explanation: The maximum result is 5 ^ 25 = 28.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        // 初始化根节点
        nodes.push_back(Node({0, 0}));

        // 建树
        for(auto x: nums)
        {
            int p = 0; // 第 p 个节点, 第 0 个节点已经初始化
            for(int i = 30; i >= 0; --i)
            {
                // 从高位枚举
                int t = x >> i & 1; // 1 往左，0 往右
                if(!nodes[p].son[t])
                {
                    nodes.push_back(Node({0, 0}));
                    nodes[p].son[t] = nodes.size() - 1; // 儿子的指针，实际是索引
                }
                p = nodes[p].son[t];
            }
        }

        // 遍历
        int res = 0;
        for(int x: nums)
        {
            int p = 0; // 遍历树的索引
            int max_xor = 0; // 当前 x 的最大异或值
            for(int i = 30; i >= 0; --i)
            {
                int t = x >> i & 1; // 希望下一节点的方向为 !t
                if(nodes[p].son[!t]) // 先判断希望的下一个节点有没有
                {
                    p = nodes[p].son[!t];
                    max_xor += 1 << i;
                }
                else
                {
                    p = nodes[p].son[t]; // 没有希望的方向，一定有另一个方向
                }
            }
            res = max(res, max_xor);
        }
        return res;
    }

private:
    // 以下就是 Trie 树的极简版
    struct Node{
        int son[2];
    };

    vector<Node> nodes;
};
