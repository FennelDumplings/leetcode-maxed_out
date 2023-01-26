// prob1268: Search Suggestions System

/*
 * https://leetcode-cn.com/problems/search-suggestions-system/
 */

#include <set>
#include <vector>
#include <string>

using namespace std;

const int ALPHABET = 26;

struct TrieNode
{
    set<string> setting;
    vector<TrieNode*> children;
    TrieNode()
    {
        children = vector<TrieNode*>(ALPHABET);
        setting = set<string>();
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
        for(const char ch: s)
        {
            TrieNode *&nxt = (iter -> children)[ch - 'a'];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
            (iter -> setting).insert(s);
        }
    }

    vector<vector<string>> search(const string& s)
    {
        int n = s.size();
        vector<vector<string>> result(n);
        TrieNode *iter = root;
        int i = 0;
        while(i < n)
        {
            char ch = s[i];
            TrieNode *nxt = (iter -> children)[ch - 'a'];
            if(!nxt)
                break;
            auto it = (nxt -> setting).begin();
            int cnt = 0;
            while(cnt < 3 && it != (nxt -> setting).end())
            {
                result[i].push_back(*it);
                ++it;
                ++cnt;
            }
            ++i;
            iter = nxt;
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
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie *trie = new Trie();
        for(const string& p: products)
            trie -> insert(p);
        return trie -> search(searchWord);
    }
};
