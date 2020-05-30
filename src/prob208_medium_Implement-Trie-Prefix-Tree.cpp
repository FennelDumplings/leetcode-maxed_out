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
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
        root = nullptr;
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *iter = root;
        for(const char c: word)
        {
            if(!(iter -> children[_to_int(c)]))
                (iter -> children)[_to_int(c)] = new TrieNode();
            iter = (iter -> children)[_to_int(c)];
        }
        iter -> terminal = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        const TrieNode* iter = find(word);
        return iter && iter -> terminal;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }

private:
    TrieNode *root;

    int _to_int(char ch) const
    {
        return ch - 'a';
    }

    const TrieNode* find(const string& prefix) const
    {
        const TrieNode* iter = root;
        for(const char c: prefix)
        {
            iter = (iter -> children)[_to_int(c)];
            if(iter == nullptr) break;
        }
        return iter;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */


