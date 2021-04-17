// prob1032: Stream of Characters

/*
 * https://leetcode-cn.com/problems/stream-of-characters/
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
        children = vector<TrieNode*>(ALPHABET, nullptr);
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

    void insert(const string& word)
    {
        int n = word.size();
        _insert(root, word, n - 1);
    }

    bool search(const string& suffixes)
    {
        int n = suffixes.size();
        bool flag = dfs(root, suffixes, n - 1);
        return flag;
    }

private:
    TrieNode *root;

    bool dfs(TrieNode* node, const string& suffixes, int pos)
    {
        if(pos == -1)
            return false;
        char cur = suffixes[pos];
        if(!(node -> children)[cur - 'a'])
            return false;
        if((node -> children)[cur - 'a'] -> terminate)
            return true;
        return dfs((node -> children)[cur - 'a'], suffixes, pos - 1);
    }

    void _insert(TrieNode* node, const string& word, int pos)
    {
        if(pos == -1)
        {
            node -> terminate = true;
            return;
        }
        char cur = word[pos];
        if(!(node -> children)[cur - 'a'])
            (node -> children)[cur - 'a'] = new TrieNode();
        _insert((node -> children)[cur - 'a'], word, pos - 1);
    }
};

class StreamChecker {
public:
    StreamChecker(vector<string>& words) {
        trie = new Trie();
        for(const string &word: words)
            trie -> insert(word);
    }

    bool query(char letter) {
        buf += letter;
        return trie -> search(buf);
    }

private:
    Trie *trie;
    string buf;
};
