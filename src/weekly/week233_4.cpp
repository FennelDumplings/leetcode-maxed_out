
#include <vector>

using namespace std;

struct Trie01Node
{
    Trie01Node *left, *right;
    int cnt;
    Trie01Node()
    {
        left = nullptr, right = nullptr;
        cnt = 0;
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
            iter -> cnt += 1;
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

    int search(int num, const int low, const int high)
    {
        Trie01Node *iter = root;
        // 给定 ai 找到
        // 使得 ai ^ aj < low 的 aj 个数 n1
        // 使得 ai ^ aj > high 的 aj 个数 n2
        // 返回 n1 + n2
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
    int countPairs(vector<int>& nums, int low, int high) {
        Trie01 trie01;
        int n = nums.size();
        for(int num: nums)
            trie01.insert(num);
        using ll = long long;
        ll result = 0;
        for(int num: nums)
            result += (n - 1) - trie01.search(num, low, high);
        return result / 2;
    }
};
