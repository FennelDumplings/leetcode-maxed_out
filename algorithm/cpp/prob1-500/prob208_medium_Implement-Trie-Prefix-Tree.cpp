// prob208: Implement Trie (Prefix Tree)

/*
 * Implement a trie with insert, search, and startsWith methods.
 */

/*
 * Example:
 * Trie trie = new Trie();
 * trie.insert("apple");
 * trie.search("apple");   // returns true
 * trie.search("app");     // returns false
 * trie.startsWith("app"); // returns true
 * trie.insert("app");
 * trie.search("app");     // returns true
 */

/*
 * Note:
 * You may assume that all inputs are consist of lowercase letters a-z.
 * All inputs are guaranteed to be non-empty strings.
 */

#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    const int ALPHABETS = 26;
    vector<TrieNode*> children;
    bool terminal;
    TrieNode()
    {
        terminal = false;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode(){}
};

class Trie {
public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete_sub_tree(root);
    }

    void insert(string word)
    {
        TrieNode *iter = root;
        for(const char c: word)
        {
            if(!(iter -> children[c - 'a']))
                (iter -> children)[c - 'a'] = new TrieNode();
            iter = (iter -> children)[c - 'a'];
        }
        iter -> terminal = true;
    }

    bool search(string word)
    {
        const TrieNode* iter = find(word);
        return iter && iter -> terminal;
    }

    bool startsWith(string prefix)
    {
        return find(prefix) != nullptr;
    }

private:
    TrieNode *root;

    void delete_sub_tree(TrieNode *node)
    {
        for(TrieNode *child: node -> children)
            if(child)
                delete_sub_tree(child);
        delete node;
        node = nullptr;
    }

    const TrieNode* find(const string& prefix) const
    {
        const TrieNode* iter = root;
        for(const char c: prefix)
        {
            iter = (iter -> children)[c - 'a'];
            if(iter == nullptr) break;
        }
        return iter;
    }
};
