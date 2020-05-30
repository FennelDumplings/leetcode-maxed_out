// prob211: Add and Search Word - Data structure design

/*
 * Design a data structure that supports the following two operations:
 * void addWord(word)
 * bool search(word)
 * search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.
 */

/*
 * Example:
 * addWord("bad")
 * addWord("dad")
 * addWord("mad")
 * search("pad") -> false
 * search("bad") -> true
 * search(".ad") -> true
 * search("b..") -> true
 * Note:
 * You may assume that all words are consist of lowercase letters a-z.
 */

#include <string>
#include <vector>

using namespace std;

const int ALPHABETS = 26;

struct TrieNode
{
    bool terminate;
    vector<TrieNode*> children;
    TrieNode()
    {
        terminate = false;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode()
    {
        for(TrieNode* child: children)
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

    void insert(const string& word)
    {
        TrieNode *iter = root;
        for(const char ch: word)
        {
            TrieNode *&nxt = (iter -> children)[_char2int(ch)];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
        }
        iter -> terminate = true;
    }

    bool search(const string& word)
    {
        return _search(root, word, 0);
    }

private:
    TrieNode *root;

    int _char2int(const char& ch)
    {
        return ch - 'a';
    }

    bool _search(TrieNode* root, const string& word, int idx)
    {
        int n = word.size();
        if(idx == n)
            return root -> terminate;
        if(word[idx] != '.')
        {
            TrieNode *nxt = (root -> children)[_char2int(word[idx])];
            if(!nxt) return false;
            return _search(nxt, word, idx + 1);
        }
        for(TrieNode *child: (root -> children))
        {
            if(child)
            {
                if(_search(child, word, idx + 1))
                    return true;
            }
        }
        return false;
    }
};

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        trie = new Trie();
    }

    ~WordDictionary() {
        if(trie)
        {
            delete trie;
            trie = nullptr;
        }
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {
        trie -> insert(word);
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return trie -> search(word);
    }

private:
    Trie *trie;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
