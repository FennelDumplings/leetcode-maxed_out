// prob1065: Index Pairs of a String

/*
 * https://leetcode-cn.com/problems/index-pairs-of-a-string/
 */

#include <vector>
#include <string>

using namespace std;

const int ALPHABET = 26;

struct TrieNode
{
    bool terminate;
    vector<TrieNode*> children;
    TrieNode()
    {
        terminate = false;
        children = vector<TrieNode*>(ALPHABET);
    }
};

class Trie
{
public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        if(root)
            _delete_sub_tree(root);
    }

    void insert(const string& s)
    {
        TrieNode *iter = root;
        for(const char &ch: s)
        {
            TrieNode *&nxt = (iter -> children)[ch - 'a'];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
        }
        iter -> terminate = true;
    }

    vector<int> search(const string& s, int i)
    {
        // 返回所有的 j: s[i..j] 匹配
        TrieNode *iter = root;
        vector<int> result;
        int j = i;
        int n = s.size();
        while(j < n)
        {
            TrieNode *&nxt = (iter -> children)[s[j] - 'a'];
            if(!nxt)
                return result;
            iter = nxt;
            if(iter -> terminate)
                result.push_back(j);
            ++j;
        }
        return result;
    }

private:
    TrieNode *root;

    void _delete_sub_tree(TrieNode* node)
    {
        for(TrieNode *child: node -> children)
            if(child)
                _delete_sub_tree(child);
        delete node;
        node = nullptr;
    }
};

class Solution {
public:
    vector<vector<int>> indexPairs(string text, vector<string>& words) {
        Trie *trie = new Trie();
        for(const string &s: words)
            trie -> insert(s);
        vector<vector<int>> result;
        int n = text.size();
        for(int i = 0; i < n; ++i)
        {
            vector<int> js = trie -> search(text, i);
            for(int j: js)
                result.push_back({i, j});
        }
        return result;
    }
};
