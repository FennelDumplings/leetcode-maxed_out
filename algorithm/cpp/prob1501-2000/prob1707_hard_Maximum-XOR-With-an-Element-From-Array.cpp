#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Trie01Node
{
    Trie01Node *left, *right;
    int minx;
    Trie01Node(int minx=INT_MAX)
    {
        left = nullptr, right = nullptr;
        this -> minx = minx;
    }
    ~Trie01Node(){}
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
            delete_subtree(root);
        }
    }

    void insert(int num)
    {
        Trie01Node *iter = root;
        iter -> minx = min(iter -> minx, num);
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
            iter -> minx = min(iter -> minx, num);
        }
    }

    bool empty() const
    {
        if(!root)
            return true;
        if(!root -> left && !root -> right)
            return true;
        return false;
    }

    int search(int x, int mi)
    {
        if(empty())
            return -1;
        /*
         * 给定 x，找到使得 x ^ a 最大的 a
         * 尽可能让高位上的 x 与 a 不同
         * 所有的数都是长度 30 捅到底的
         */
        Trie01Node *iter = root;
        if(iter -> minx > mi)
            return -1;
        int a = 0;
        for(int i = 30; i >= 0; --i)
        {
            if((x >> i) & 1)
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
                if(iter -> right && iter -> right -> minx <= mi)
                {
                    iter = iter -> right;
                    a |= (1 << i);
                }
                else
                    iter = iter -> left;
            }
        }
        return a ^ x;
    }

private:
    Trie01Node *root;

    void delete_subtree(Trie01Node* node)
    {
        if(node -> left)
            delete_subtree(node -> left);
        if(node -> right)
            delete_subtree(node -> right);
        delete node;
        node = nullptr;
    }
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        int m = queries.size();
        Trie01 *trie01 = new Trie01();
        for(int x: nums) trie01 -> insert(x);
        vector<int> result(m);
        for(int i = 0; i < m; ++i)
        {
            result[i] = trie01 -> search(queries[i][0], queries[i][1]);
        }
        return result;
    }
};
