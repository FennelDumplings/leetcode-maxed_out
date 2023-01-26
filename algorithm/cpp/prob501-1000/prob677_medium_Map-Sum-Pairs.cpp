// prob677: Map Sum Pairs

/*
 * Implement a MapSum class with insert, and sum methods.
 * For the method insert, you'll be given a pair of (string, integer). The string represents the key and the integer
 * represents the value. If the key already existed, then the original key-value pair will be overridden to the new one.
 * For the method sum, you'll be given a string representing the prefix, and you need to return the sum of all the pairs'
 * value whose key starts with the prefix
 */

/*
 * Example 1:
 * Input: insert("apple", 3), Output: Null
 * Input: sum("ap"), Output: 3
 * Input: insert("app", 2), Output: Null
 * Input: sum("ap"), Output: 5
 */

#include <string>
#include <vector>

using namespace std;

const int ALPHABETS = 26;

struct TrieNode
{
    vector<TrieNode*> children;
    int value;
    bool terminate;
    TrieNode()
    {
        terminate = false;
        value = 0;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode()
    {
        for(TrieNode *child: children)
        {
            if(child)
            {
                delete child;
                child = nullptr;
            }
        }
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
        {
            delete root;
            root = nullptr;
        }
    }

    void insert(const string& word, int val)
    {
        TrieNode *iter = root;
        for(char ch: word)
        {
            TrieNode *&next = (iter -> children)[_char2int(ch)];
            if(!next)
                next = new TrieNode();
            iter = next;
        }
        iter -> terminate = true;
        iter -> value = val;
    }

    int sum(const string& prefix)
    {
        TrieNode *it = _find(prefix);
        if(!it) return 0;
        int result = 0;
        dfs(it, result);
        return result;
    }

private:
    TrieNode *root;

    int _char2int(char ch)
    {
        return ch - 'a';
    }

    void dfs(TrieNode* root, int& result)
    {
        if(root -> terminate)
            result += root -> value;
        for(TrieNode *child: (root -> children))
        {
            if(child)
            {
                dfs(child, result);
            }
        }
    }

    TrieNode* _find(const string& word)
    {
        TrieNode *iter = root;
        for(char ch: word)
        {
            TrieNode *&next = (iter -> children)[_char2int(ch)];
            if(!next)
                return nullptr;
            iter = next;
        }
        return iter;
    }
};

class MapSum {
public:
    /** Initialize your data structure here. */
    MapSum() {
        trie = new Trie();
    }

    ~MapSum()
    {
        if(trie)
        {
            delete trie;
            trie = nullptr;
        }
    }

    void insert(string key, int val) {
        trie -> insert(key, val);
    }

    int sum(string prefix) {
        return trie -> sum(prefix);
    }

private:
    Trie *trie;
};

