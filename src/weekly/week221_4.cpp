
#include <vector>

using namespace std;

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

    bool dfs(Trie01Node* node, int i, int& a, const int xi, const int mi)
    {
        if(a > mi)
            return false;
        if(i == -1)
            return true;

        if((xi >> i) & 1)
        {
            if(node -> left)
                if(dfs(node -> left, i - 1, a, xi, mi))
                    return true;
            if(node -> right)
            {
                a |= (1 << i);
                if(dfs(node -> right, i - 1, a, xi, mi))
                    return true;
                a &= ~(1 << i);
            }
        }
        else
        {
            if(node -> right)
            {
                a |= (1 << i);
                if(dfs(node -> right, i - 1, a, xi, mi))
                    return true;
                a &= ~(1 << i);
            }
            if(node -> left)
                if(dfs(node -> left, i - 1, a, xi, mi))
                    return true;
        }
        return false;
    }

    int search(int xi, int mi)
    {
        // 给定 ai，找到使得 ai ^ aj 最大的 aj
        // 尽可能让高位上的 ai 与 aj 不同
        // 所有的数都是长度 30 捅到底的
        int a = 0;
        dfs(root, 30, a, xi, mi);
        return a ^ xi;
    }

private:
    Trie01Node *root;
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        Trie01 *trie = new Trie01();
        int minx = 1e5 + 1;
        for(int i: nums)
        {
            minx = min(minx, i);
            trie -> insert(i);
        }
        int m = queries.size();
        vector<int> result(m);
        for(int i = 0; i < m; ++i)
        {
            if(queries[i][1] < minx)
                result[i] = -1;
            else
                result[i] = trie -> search(queries[i][0], queries[i][1]);
        }
        return result;
    }
};
