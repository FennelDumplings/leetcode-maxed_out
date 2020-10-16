// prob386: Lexicographical Numbers

/*
 * https://leetcode-cn.com/problems/lexicographical-numbers/
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct TrieNode {
    const int ALPHABETS = 10;
    vector<TrieNode*> children;
    bool terminal;
    TrieNode()
    {
        terminal = false;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode()
    {
        for(TrieNode *child: children)
            if(child)
            {
                delete child;
                child = nullptr;
            }
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
        root = nullptr;
    }

    void insert(int num) {
        TrieNode *iter = root;
        vector<int> digits;
        while(num)
        {
            int c = num % 10;
            num /= 10;
            digits.push_back(c);
        }
        reverse(digits.begin(), digits.end());
        for(int c: digits)
        {
            if(!(iter -> children[c]))
                (iter -> children)[c] = new TrieNode();
            iter = (iter -> children)[c];
        }
        iter -> terminal = true;
    }

    bool search(int num) {
        const TrieNode* iter = find(num);
        return iter && iter -> terminal;
    }

    bool startsWith(int prefix) {
        return find(prefix) != nullptr;
    }

    vector<int> traverse()
    {
        int item = 0;
        vector<int> result;
        dfs(root, item, result);
        return result;
    }

private:
    TrieNode *root;

    void dfs(TrieNode* node, int item, vector<int>& result)
    {
        if(node -> terminal)
        {
            result.push_back(item);
        }
        item *= 10;
        for(int i = 0; i <= 9; ++i)
        {
            TrieNode *son = node -> children[i];
            if(son)
            {
                item += i;
                dfs(son, item, result);
                item -= i;
            }
        }
    }

    const TrieNode* find(int prefix) const
    {
        const TrieNode* iter = root;
        vector<int> digits;
        while(prefix)
        {
            int c = prefix % 10;
            prefix /= 10;
            digits.push_back(c);
        }
        reverse(digits.begin(), digits.end());
        for(int c: digits)
        {
            iter = (iter -> children)[c];
            if(iter == nullptr) break;
        }
        return iter;
    }
};

class Solution_2 {
public:
    vector<int> lexicalOrder(int n) {
        Trie trie;
        for(int i = 1; i <= n; ++i)
            trie.insert(i);
        vector<int> result = trie.traverse();
        return result;
    }
};



class Solution {
public:
    vector<int> lexicalOrder(int n) {
        int item = 0;
        vector<int> result;
        dfs(item, result, n);
        return result;
    }

    void dfs(int item, vector<int>& result, const int n)
    {
        if(item > n)
            return;
        if(item > 0)
            result.push_back(item);
        item *= 10;
        for(int i = 0; i <= 9; ++i)
        {
            if(item == 0 && i == 0)
                continue;
            item += i;
            dfs(item, result, n);
            item -= i;
        }
    }
};
