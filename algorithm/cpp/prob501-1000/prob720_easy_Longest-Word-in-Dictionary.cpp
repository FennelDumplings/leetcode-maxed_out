// prob720: Longest Word in Dictionary

/*
 * Given a list of strings words representing an English Dictionary, find the longest word in words that can be built one character at a time by other words in words. If there is more than one possible answer, return the longest word with the smallest lexicographical order.
 * If there is no answer, return the empty string.
 */

/*
 * Example 1:
 * Input:
 * words = ["w","wo","wor","worl", "world"]
 * Output: "world"
 * Explanation:
 * The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
 * Example 2:
 * Input:
 * words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
 * Output: "apple"
 * Explanation:
 * Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".
 */

/*
 * Note:
 * All the strings in the input will only contain lowercase letters.
 * The length of words will be in the range [1, 1000].
 * The length of words[i] will be in the range [1, 30].
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
        root -> terminate = true;
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

    string stat()
    {
        string result = "";
        string cur = "";
        dfs(root, result, cur);
        return result;
    }

private:
    TrieNode *root;

    void dfs(TrieNode* root, string& result, string& cur)
    {
        for(int i = 0; i < ALPHABETS; ++i)
        {
            TrieNode *child = (root -> children)[i];
            if(!child || !child -> terminate)
            {
                if(cur.size() > result.size())
                    result = cur;
                continue;
            }
            cur += 'a' + i;
            dfs(child, result, cur);
            cur.pop_back();
        }
    }

    int _char2int(const char ch)
    {
        return ch - 'a';
    }
};

class Solution {
public:
    string longestWord(vector<string>& words) {
        Trie *trie = new Trie();
        for(const string word: words)
            trie -> insert(word);
        string result = trie -> stat();
        delete trie;
        trie = nullptr;
        return result;
    }
};
