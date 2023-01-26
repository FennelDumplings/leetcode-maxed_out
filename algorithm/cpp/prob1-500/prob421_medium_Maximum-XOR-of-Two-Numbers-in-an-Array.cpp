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

// ai ^ aj
// 给定 ai，找到使得 ai ^ aj 最大的 aj
// 尽可能让高位上的 ai 与 aj 不同
struct Trie01Node
{
    Trie01Node *left, *right;
    Trie01Node()
    {
        left = nullptr, right = nullptr;
    }
    ~Trie01Node()
    {
        if(left)
        {
            delete left;
            left = nullptr;
        }
        if(right)
        {
            delete right;
            right = nullptr;
        }
    }
};

class Trie01
{
public:
    Trie01()
    {
        root = new Trie01Node();
    }

    ~Trie01()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void insert(int num)
    {
        Trie01Node *iter = root;
        // 从高位到低位枚举
        for(int i = 30; i >= 0; --i)
        {
            if((num >> i) & 1)
            {
                if(!iter -> right)
                    iter -> right = new Trie01Node();
                iter = iter -> right;
            }
            else
            {
                if(!iter -> left)
                    iter -> left = new Trie01Node();
                iter = iter -> left;
            }
        }
    }

    int search(int num)
    {
        Trie01Node *iter = root;
        // 给定 ai，找到使得 ai ^ aj 最大的 aj
        // 尽可能让高位上的 ai 与 aj 不同
        // 所有的数都是长度 30 捅到底的
        int a = 0;
        for(int i = 30; i >= 0; --i)
        {
            if((num >> i) & 1)
            {
                if(iter -> left)
                    iter = iter -> left;
                else
                {
                    iter = iter -> right;
                    a |= (1 << i);
                }
            }
            else
            {
                if(iter -> right)
                {
                    iter = iter -> right;
                    a |= (1 << i);
                }
                else
                    iter = iter -> left;
            }
        }
        return a ^ num;
    }

private:
    Trie01Node *root;
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie01 trie01;
        for(int num: nums)
            trie01.insert(num);
        int result = 0;
        for(int num: nums)
            result = max(result, trie01.search(num));
        return result;
    }
};

// -----------------------------------

class Solution_2 {
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
